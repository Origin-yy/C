#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int write_timeout_select(int fd, void *buf, size_t n, u_int32_t time) {
  //设置超时时间

  fd_set wSet;
  FD_ZERO(&wSet);
  FD_SET(fd, &wSet);

  struct timeval timeout;
  memset(&timeout, 0, sizeof(timeout));
  timeout.tv_sec = time;
  timeout.tv_usec = 0;
  // select加超时，阻塞并等待写就绪
  int r;
  while (1) {
    r = select(fd + 1, NULL, &wSet, NULL, &timeout);
    if (r < 0) {
      if (errno == EINTR)
        continue;
      return r;
    } else if (r == 0) {
      errno = ETIMEDOUT; //设置errno为超时
      return -1;
    } else {
      break;
    }
  }

  //开写
  int writeNum;
  writeNum = write(fd, buf, n);
  return writeNum;
}

int read_timeout_select(int fd, void *buf, size_t n, u_int32_t time) {
  //设置超时时间
  fd_set rSet;
  FD_ZERO(&rSet);
  FD_SET(fd, &rSet);

  struct timeval timeout;
  memset(&timeout, 0, sizeof(timeout));
  timeout.tv_sec = time;
  timeout.tv_usec = 0;
  // select加上超时,并阻塞等待读就绪
  int r;
  while (1) {
    r = select(fd + 1, &rSet, NULL, NULL, &timeout);
    if (r < 0) {
      if (errno == EINTR)
        continue;
      return r;
    } else if (r == 0) {
      errno = ETIMEDOUT;
      return -1;
    } else {
      break;
    }
  }

  //开读
  int readnum;
  readnum = read(fd, buf, n);
  return readnum;
}

void handler(int s) {
  printf("SIGALRM信号到达。\n");
  return;
}
int write_timeout_alarm(int fd, void *buf, size_t n, u_int32_t time) {
  struct sigaction act;
  act.sa_handler = handler;
  sigemptyset(&act.sa_mask);
  act.sa_flags = 0;
  act.sa_flags |= SA_INTERRUPT; //设置该选项后，中断的系统调用不会自动重启
  if (sigaction(SIGALRM, &act, NULL) == -1) {
    perror("sigaction");
    exit(-1);
  }

  alarm(time);
  int readnum = write(0, buf, sizeof(buf)); //从标准输入读取字符
  alarm(0);

  return readnum;
}

int read_timeout_alarm(int fd, void *buf, size_t n, u_int32_t time) {
  struct sigaction act;
  act.sa_handler = handler;
  sigemptyset(&act.sa_mask);
  act.sa_flags = 0;
  act.sa_flags |= SA_INTERRUPT; //设置该选项后，中断的系统调用不会自动重启
  if (sigaction(SIGALRM, &act, NULL) == -1) {
    perror("sigaction");
    exit(-1);
  }

  alarm(time);
  int writenum = write(1, buf, sizeof(buf)); //从标准输入读取字符
  alarm(0);

  return writenum;
}

int main() {
  char buf[10];
  char buf_write[10] = "";
  errno = ETIMEDOUT;
  int r = read_timeout_select(0, buf, sizeof(buf), 5); //从标准输入读取字符
  if (r == -1)
    printf("read()超时返回\n");
  else
    printf("read读取%d字节\n", r);
  return 0;
}