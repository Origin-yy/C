#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int connectToHost(int lfd, char *ip, unsigned short port);

int createsocket();
int sendMsg(int fd, const char *msg, int len);
ssize_t writen(int fd, const void *buf, size_t n);

int main() {
  int r;
  char temp[1001];

  int fd = socket(AF_INET, SOCK_STREAM, 0);   //创建客户端socket
  
  //初始化一个IPv4地址
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(9526);

  inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr.s_addr);
  r = connect(fd, (struct sockaddr *)&addr, sizeof(addr));
  if (r > 0)
    printf("客户端连接成功\n");
  else {
    printf("客户端理连接失败.\n");
    exit(1);
  }
  int length = 0;
  int fd1 = open("english.txt", O_RDONLY);
  while ((length = read(fd1, temp, rand() % 1000)) > 0) {
    sendMsg(fd, temp, length);
    memset(temp, 0, sizeof(temp));
    usleep(300);
  }
  sleep(10);
}

int createsocket() {
  int lfd = socket(AF_INET, SOCK_STREAM, 0);
  if (lfd == -1) {
    perror("socket error");
    return -1;
  } else {
    printf("套接字创建成功\n");
    return lfd;
  }
}

ssize_t writen(int fd, const void *buf, size_t n) {
  ssize_t numwriten;
  size_t totwriten;
  const char *p;

  p = buf;
  for (totwriten = 0; totwriten < n;) {
    numwriten = write(fd, p, n - totwriten);

    if (numwriten <= 0) {
      if (numwriten == -1 && errno == EINTR)
        continue;
      else
        return -1;
    }
    totwriten += numwriten;
    p += numwriten;
  }
  return totwriten;
}

int sendMsg(int fd, const char *msg, int len) {
  if (fd < 0 || msg == NULL || len <= 0) {
    return -1;
  }
  char *data = (char *)malloc(sizeof(char) * (len + 4));
  int biglen = htonl(len);
  memcpy(data, &biglen, 4);
  memcpy(data + 4, msg, len);
  int ret;
  ret = writen(fd, data, len + 4);
  if (ret == -1) {
    perror("send error");
    close(fd);
  }
  return ret;
}