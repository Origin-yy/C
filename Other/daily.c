#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
 
void handler(int s)
{
	printf("信号到达。\n");
	return;
}

int readn(int fd, void* buf,int n)
{
	struct sigaction act;  
	act.sa_handler = handler;  
	sigemptyset(&act.sa_mask);  
	act.sa_flags = 0;  
	act.sa_flags |= SA_INTERRUPT;  //设置该选线系统调用不会自动重启
	if(sigaction(SIGALRM, &act, NULL) == -1)  
	{
		perror("sigaction");
		exit(-1);
	}
	
	alarm(5);
	read(0, buf, sizeof(buf));  //从标准输入读取字符

	return 0;
}

int main()
{	
	char buf[10];

	readn(0, buf, sizeof(buf));  //从标准输入读取字符
	printf("read()超时返回\n");

    return 0;
}