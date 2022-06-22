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

int recvMsg(int fd, char **msg);
int readn(int fd, char *buf, int size);

int main() {
  int s;
  //创建一个socket
  int listenfd;
  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  if (listenfd < 0) {
    printf("socket() failed.");
    exit(0);
  }

  //初始化一个ipv4地址（通配地址，接听所有链接）
  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(struct sockaddr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(55000);
  addr.sin_addr.s_addr = htonl(INADDR_ANY);

  //绑定到通配地址
  s = bind(listenfd, (struct sockaddr *)&addr, sizeof(addr));
  if (s == -1) {
    printf("bind() failed.\n");
    exit(0);
  }

  listen(listenfd, 10); //监听所有连接

  printf("服务器已运行,等待客户端连接。\n");

  int confd = accept4(listenfd, (struct sockaddr *)NULL, NULL,
                      SOCK_NONBLOCK); //只接入一个连接请求,非阻塞
  if (confd != -1)
    printf("客户端已连接。\n");
  else {
    printf("accept() filaed.\n");
    exit(0);
  };

  // for循环不断从socket中取数据
  for (;;) {

    int len = 0;
    printf("start\n");

    readn(confd, (char *)&len, sizeof(int)); //读到字符串大小
    len = ntohl(len);

    printf("接收到的字符串大小为：%d\n", len);

    char *buf = (char *)malloc(len); // buf用来存一个字符串
    read(confd, buf, len);           //读到字符串

    //printf("接收到的字符串为：\n%s\n", buf);

    printf("已提交一个字符串\n");

    free(buf);
  }
  close(confd);
  // Put your code Here!
}

int readn(int fd, char *buf, int n) {
  int nleft = 0;
  int nread = 0;
  int *pread_buf = NULL;

  pread_buf = (int *)buf;
  nleft = n;

  while (nleft > 0) {
    nread = recv(fd, (char *)pread_buf, nleft, 0);
    if (nread < 0) {
      if (EINTR == errno || EWOULDBLOCK == errno || EAGAIN == errno) {
        nread = 0;
      } else {
        return -1;
      }
    } else if (nread == 0) {
      break;
    } else {
      nleft -= nread;
      pread_buf += nread;
    }
  }
  return (ssize_t)(n - nleft);
}
int recvMsg(int fd, char **msg) {
  int len = 0;
  readn(fd, (char *)&len, 4);
  len = ntohl(len);
  printf("接收到的 数据块大小 %d\n", len);
  char *data = (char *)malloc(len + 1);
  int Len = readn(fd, data, len);
  if (Len == 0) {
    printf("对方断开链接\n");
    close(fd);
  } else if (len != Len) {
    printf("数据接收失败\n");
  }
  data[len] = '\0';
  *msg = data;
  return Len;
}
