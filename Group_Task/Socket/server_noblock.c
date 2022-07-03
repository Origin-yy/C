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

int readn(int fd, void *buf, int n) {
    int left = 0;
    int had = 0;
    int *ptr = NULL;

    ptr = (int *) buf;
    left = n;

    while (left > 0) {
        had = read(fd, (char *) ptr, left);
        if (had == -1) {
            if (errno == EINTR || errno == EWOULDBLOCK|| errno == EAGAIN) {
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
    return n - left;
}

int main() {
  // Server 端的监听地址
  int s;
  auto test = TestInit("0.0.0.0:1234");
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

  listen(listenfd, 128); //监听所有连接
  printf("服务器已运行,等待客户端连接。\n");

  int epfd = epoll_create(1000); //创建监听红黑树
  struct epoll_event temp, ep[1024];
  temp.data.fd = listenfd;
  temp.events = EPOLLIN;
  epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &temp); //将监听套接字加入监听红黑树

  while (1) {
    int nready = epoll_wait(epfd, ep, 1024, -1);
    for (int i = 0; i < nready; i++) {
      //如果是监听socket就绪说明有客户端接入，将接入客户端后返回的客户端socket加入epoll中
      if (ep[i].data.fd == listenfd) {
        int confd = accept(listenfd, (struct sockaddr *)NULL, NULL);
        if (confd != -1)
          printf("客户端已连接。\n");
        else {
          printf("accept() filaed.\n");
          exit(0);
        };
        temp.data.fd = confd;
        temp.events = EPOLLIN;
        epoll_ctl(epfd, EPOLL_CTL_ADD, confd, &temp);
        printf("客户端%d连接成功\n", confd);
      }
      //其他socket就绪说明客户端socket上有可读事件，有数据到来，读取数据。
      else {
        int confd = ep[i].data.fd;
        int had = 0; //已经读的数据大小
        int len = 0;
        //先读字符串大小
        s = readn(confd, (char *)&len, sizeof(int)); //读到字符串大小
        //如果返回值是0，说明连接断开，则将该socket移除并关闭。
        if (s == 0) {
          temp.data.fd = confd;
          temp.events = EPOLLIN;
          epoll_ctl(epfd, EPOLL_CTL_DEL, confd, &temp);
          printf("对端socket已关闭.\n");
          close(confd);
        } else {
          len = ntohl(len);

          //再读字符串本身
          char *buf = (char *)malloc(len);
          s = readn(confd, buf, len); //读到字符串
          if (s == 0) {
            printf("对端socket已关闭.\n");
            close(confd);
          } else if (s == -1) {
            printf("readn() failed.\n");
            close(confd);
            confd = -1;
            exit(0);
          }
          printf("接收到的字符串为：\n%s\n", buf);
          printf("接收到的字符串大小为：%d\n", len);

          std::string str(buf, len);
          test->commit(std::move(str));
          free(buf);
        }
      }
    }
  }
  close(listenfd);
  // Put your code Here!
}