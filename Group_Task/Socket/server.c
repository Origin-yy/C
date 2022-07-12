#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h> 
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<errno.h>
#include<strings.h>
#include<stdlib.h>
#include<string.h>
#include<sys/epoll.h>
//绑定+监听
int setListen(int lfd,unsigned short port);
int acceptConn(int lfd,struct sockaddr_in*addr);

int createsocket();
int recvMsg(int fd,char**msg);
ssize_t readn(int fd, void*buf,size_t n);

#define MAXLEN 1000
int main()
{
  int i;
  int ret=-1;//检测返回值
  int cfd;
  char *buf;
  int listenfd=createsocket();
  if(listenfd==-1)
    return -1;
 struct sockaddr_in saddr;
 saddr.sin_family=AF_INET;
 saddr.sin_port=htons(9526);
 saddr.sin_addr.s_addr=INADDR_ANY;
 ret=bind(listenfd,(struct sockaddr*)&saddr,sizeof(saddr));
 if(ret==-1)
 {
   perror("bind error");
   exit(-1);
 }
 ret=listen(listenfd,128);


 int epfd=epoll_create(MAXLEN);  //创建监听红黑树
 struct epoll_event temp,ep[1024];
 temp.data.fd=listenfd;
 temp.events=EPOLLIN;
 epoll_ctl(epfd,EPOLL_CTL_ADD,listenfd,&temp);//将监听套接字加入监听红黑树


while(1)
{
  ret=epoll_wait(epfd,ep,1024,-1);
  for(i=0;i<ret;i++)
  {
    if(ep[i].data.fd==listenfd){
      cfd=acceptConn(listenfd,NULL);
      temp.data.fd=cfd;
      temp.events=EPOLLIN;
      epoll_ctl(epfd,EPOLL_CTL_ADD,cfd,&temp);
      printf("客户端%d连接成功\n",cfd);
    }else {
      int ccfd=ep[i].data.fd;
      int len=recvMsg(ccfd,&buf);
     if(len==0){
        temp.data.fd=ccfd;
        temp.events=EPOLLIN;
        epoll_ctl(epfd,EPOLL_CTL_DEL,ccfd,&temp);
        free(buf);
      }else {
        printf("%s\n\n\n\n",buf);
        free(buf);
      }
      sleep(1);
    }
  }
}

 close(listenfd);
  return 0;
}

int createsocket()
{
  int lfd=socket(AF_INET,SOCK_STREAM,0);
  if(lfd==-1)
  {
    perror("socket error");
    return -1;
  }
  else 
  {
    printf("套接字创建成功\n");
    return lfd;
  }
}

int setListen(int lfd,unsigned short port)
{
  struct sockaddr_in saddr;
  saddr.sin_family=AF_INET;
  saddr.sin_port=htons(port);
  saddr.sin_addr.s_addr=INADDR_ANY;
  int ret=0;
  ret=bind(lfd,(struct sockaddr*)&saddr,sizeof(saddr));
  if(ret==-1)
  {
    perror("bind error");
    return -1;
  }
  else 
  {
    printf("套接字地址绑定成功\n");
  }
  listen(lfd,128);
  return 1;
}
int acceptConn(int lfd,struct sockaddr_in*addr)
{
  int cfd=-1;
  if(addr==NULL)
  {
    cfd=accept(lfd,NULL,NULL);
    return cfd;
  }
  socklen_t len = sizeof(*addr);
  cfd=accept(lfd,(struct sockaddr*)&addr,&len);
  return cfd;
}
int connectToHost(int  lfd,char*ip,unsigned short port)
{
  struct sockaddr_in caddr;
  caddr.sin_family=AF_INET;
  caddr.sin_port=htons(port);
  inet_pton(AF_INET,ip,&caddr.sin_addr.s_addr);
  int fd= connect(lfd,(struct sockaddr*)&caddr,sizeof(caddr));
  printf("成功与客户端建立链接\n");
  return fd;
}

ssize_t readn(int fd, void*buf,size_t n)
{
  ssize_t numread;
  size_t totread;
  char *p;

  p = buf;
  for(totread = 0; totread < n;)
  {
    numread= read(fd, p, n - totread);

    if(numread == 0)
      return totread;
    if(numread == -1)
    {
      if(errno == EINTR)
        continue;
      else
        return -1;
    }
    totread += numread;
    p += numread;
  }
  return totread;
}

int recvMsg(int fd,char**msg)
{
  int len=0;
  readn(fd,(char*)&len,4);
  len=ntohl(len);
  printf("接收到的 数据块大小 %d\n",len);
  char * data=(char*)malloc(len+1);
  int Len=readn(fd,data,len);
  if(Len==0)
  { 
      printf("对方断开链接\n");
      close(fd);    
  }
  else if(len!=Len)
  {
    printf("数据接收失败\n");
  }
  data[len]='\0';
  *msg=data;
  return Len;
}

