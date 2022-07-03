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

int writen(int connfd, const void *buf, int nums) {
  int left = 0;
  int had = 0;
  char *ptr = NULL;

  if ((connfd <= 0) || (buf == NULL) || (nums < 0)) {
    return -1;
  }

  ptr = (char *)buf;
  left = nums;

  while (left > 0) {
    had = write(connfd, ptr, left);
    if (had == -1) {
      if (errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN) {
        had = 0;
      } else {
        return -1;
      }
    } else if (had == 0) {
      return 0;
    } else {
      left -= had;
      ptr += had;
    }
  }

  return nums;
}

int main() {
  // Server 端的监听地址
  int s;
  auto msg = InitTestClient("192.168.30.170:1234");

  //创建一个socket
  int sockfd;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    printf("socket() failed.");
    exit(0);
  }

  //初始化一个ipv4地址
  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(struct sockaddr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(55000);
  inet_pton(AF_INET, "192.168.30.148", &addr.sin_addr);

  //连接我的电脑的通配地址上的socket
  s = connect(sockfd, (struct sockaddr *)&addr, sizeof(addr));
  if (s == -1) {
    printf("connect() failed.\n");
    exit(0);
  }
  //设置非阻塞
  int flags = fcntl(sockfd, F_GETFL, 0);
  fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);
  // pop一个字符串，字符串大小在前，字符串本身在后,合并在一起发送
  for (;;) {

    int len = 0; //每个字符串的大小

    auto str = msg->pop();
    const char *buf = str.data();

    len = str.size();
    int net_len = htonl(len);
    if (len == 0)
      continue;
    printf("发送的字符串为：\n%s\n发送的字符串长度为:%d\n", buf, len);

    //字符串的大小和本身合并在一起，放到ready中
    char *ready = (char *)calloc(len + sizeof(len), sizeof(char));
    memcpy(ready, &net_len, sizeof(net_len));
    memcpy(ready + sizeof(net_len), buf, len);

    s = writen(sockfd, ready, len + (int)sizeof(int));
    if (s == -1) {
      printf("write() failed.\n");
      close(sockfd);
      sockfd = -1;
      exit(0);
    } else if (s == 0) {
      printf("对端socket已关闭.\n");
      close(sockfd);
      exit(0);
    }

    int temp = htonl(*(int *)ready);

    free(ready);
  }
  close(sockfd);
  // Put your code Here!
}