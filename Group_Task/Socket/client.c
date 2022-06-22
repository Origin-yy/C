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

int sendMsg(int fd, const char *msg, int len);
int writen(int fd, char *msg, int size);

int main() {
  int s;
  //创建一个socket
  int sockfd;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    printf("socket failed.");
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

  //获取一个字符串，大小在前，字符串在后,合并在一起发送
  int len = 0; //每个字符串的大小
  char buf[1001];

  int fd1 = open("test.txt", O_RDONLY);

  while (len = read(fd1, buf, rand() % 20) > 0) {
    printf("获取的字符串为：\n%s.\n长度为:%d\n", buf, len);

    char *ready = (char *)calloc(len + sizeof(len), sizeof(char));

    int net_len = htonl(len);

    memcpy(ready, &net_len, sizeof(net_len));
    memcpy(ready + sizeof(net_len), buf, len);

    printf("sizeof(ready):%d\n", len + (int)sizeof(int));

    s = writen(sockfd, ready, len + (int)sizeof(int));
    if (s == -1) {
      printf("writen() failed.\n");
      close(sockfd);
      exit(0);
    }

    printf("发送的数据块大小为：%lu.\n", len + sizeof(len));

    int temp = htonl(*(int *)ready);
    printf("发送的字符串大小为：%d .\n", temp);

    free(ready);
    usleep(300);
  }
  // Put your code Here!
}
int writen(int fd, char *msg, int size) {
  char *buf = msg;
  int count = size;
  while (count > 0) {
    int len = send(fd, buf, count, 0);
    if (len == -1) {
      return -1;
    } else if (len == 0) {
      continue;
    }
    buf += len;
    count -= len;
  }
  return size;
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