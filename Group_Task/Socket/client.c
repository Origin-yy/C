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

//客户端
int connectToHost(int lfd, char*ip,unsigned short port);


int createsocket();
int sendMsg(int fd,const char*msg,int len);
int recvMsg(int fd,char**msg);
ssize_t writen(int fd, const void* buf,size_t n);
ssize_t readn(int fd, void*buf,size_t n);

int main()
{
  char temp[1001];
  int fd=socket(AF_INET,SOCK_STREAM,0);
  struct sockaddr_in caddr;
  caddr.sin_family=AF_INET;
  caddr.sin_port=htons(9526);
  inet_pton(AF_INET,"127.0.0.1",&caddr.sin_addr.s_addr);
  connect(fd,(struct sockaddr*)&caddr,sizeof(caddr));
  printf("客户端连接成功\n");
  if(fd==-1)
    return -1;
  
  int length=0;
  int fd1=open("english.txt",O_RDONLY);
  while((length=read(fd1,temp,rand()%1000))>0)
  {
    sendMsg(fd,temp,length);
    memset(temp,0,sizeof(temp));
    usleep(300);
  }
  sleep(10);

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
  socklen_t len=sizeof(addr);
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

ssize_t writen(int fd, const void* buf,size_t n)
{
  ssize_t numwriten;
  size_t totwriten;
  const char *p;

  p = buf;
  for(totwriten = 0; totwriten < n;)
  {
    numwriten = write(fd, p, n - totwriten);

    if(numwriten <= 0)
    {
      if(numwriten == -1 && errno == EINTR)
        continue;
      else
        return -1;
    }
    totwriten += numwriten;
    p += numwriten;

  }
  return totwriten;
}

int sendMsg(int fd,const char*msg,int len)
{
  if(fd<0||msg==NULL||len<=0)
  {
    return -1;
  }
  char*data=(char*)malloc(sizeof(char)*(len+4));
  int biglen=htonl(len);
  memcpy(data,&biglen,4);
  memcpy(data+4,msg,len);
  int ret;
  ret=writen(fd,data,len+4);
  if(ret==-1)
  {
    perror("send error");
    close(fd);
  }
  return ret;
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

