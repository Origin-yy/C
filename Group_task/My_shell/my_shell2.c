#include <stdio.h>
#include <unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<ctype.h>
#include <stdlib.h>
#include<wait.h>
#include<string.h>
#include<signal.h>

char his_workpath[100][256] = {'\0'};   //记录历史工作目录
int h = 0;                  //历史工作目录下标
int cmd_num=0;              //按空格切割后的命令个数
char buf[1024];             //存储用户的输入（未解析的字符串）
char cmd_list[100][256];    //按空格切割后的命令列表
int pid;                    //存储子进程的进程号
char *pipe_file="temp.txt"; //用做管道的文件
int flag[100][2];           //管道的输入输出重定向标记
char *file[100][2]={0};     //重定向的文件
char *argv[100][100];       //三维数组，每一个二维数组代表一个可执行程序的参数列表
int pipe_num=0;             //管道个数
int background=0;           //判断是否为有后台运行
int one = 0;                //保证“已运行”只提示一次

//实现cd命令的实现
int my_cd(char *buf)
{
    if(strcmp("-",buf) != 0)
    {
        if(chdir(buf)<0)
            return 0;
        else
            return 1;
    }
    else 
    {
        if(h > 1 && chdir(his_workpath[h-2])<0)
            return 0;
        else
            return 1;
    }
}
//打印导航栏的函数
void printf_hand()
{
    char *hand1 = "yuanye@my_shell";   //保存导航栏
    char *hand2 = NULL;                //用于保存当前工作目录
    hand2 = getcwd(NULL,0);            //获取当前工作目录
    strcpy(his_workpath[h],hand2);
    h++;
    //如果当前工作目录有“/home/yuanye”，则将其改为“~”
    if(strncmp(hand2,"/home/yuanye",12) == 0)
    {
        hand2+11;
        strncpy(hand2+11,"~",1);
        printf("\e[1;32m%-s\e[0m:\e[1;34m%-s\e[0m",hand1,hand2+11);
    }
    else
    {
        printf("\e[1;32m%-s\e[0m:\e[1;34m%-s\e[0m",hand1,hand2);
    }
    free(hand2);
    hand2=NULL;
}
//获取用户输入的函数
void get_input()
{
    int len = 0;    //保存用户输入的长度
    char ch;    
    //逐个字符读取，当读到回车时停止(未读入\n)
    ch = getchar();
    while (len < 1024 && ch != '\n')
    {
        buf[len++] = ch;
        ch = getchar();
    }
    //用户输入不可以超过256个字符
    if(len >= 1024)
    {
        perror("command is too long\n");
        exit(-1);
    }
    //在结尾手动填上\0
    buf[len] = '\0';
printf("buf:%s\n",buf);
}
//切割用户输入的函数
void cut_input() 
{
    //解析出每一个命令（空格分割）
    char *ptr;
    char *old;
    ptr = strtok_r(buf," ",&old);
    while(ptr != NULL)
    {
        strcpy(cmd_list[cmd_num],ptr) == NULL;
        cmd_num += 1;
        ptr = strtok_r(NULL," ",&old);
        if(cmd_num > 99)
           printf("命令太多了\n");
    }
}
//解析命令
void analazy_command() 
{
	//管道个数和管道的输入输出重定向标记初始化
    pipe_num=0;
	for(int i=0;i<100;i++)
     {
		flag[i][0]=flag[i][1]=0;
		file[i][0]=file[i][1]=0;
		for(int j=0;j<100;j++)
			argv[i][j]=0;
	}

	for(int i=0;i<cmd_num;i++) 
        argv[0][i]=cmd_list[i];//初始化第一个参数
	argv[0][cmd_num]=NULL;
	int a=0;//当前命令参数的序号
	for(int i=0;i<cmd_num;i++) 
    {
        //判断是否存在管道
		if(strcmp(cmd_list[i],"|")==0) 
        {//c语言中字符串比较只能用strcmp函数
			argv[pipe_num][a++]=NULL;
			pipe_num++;
			a=0;
		}
		else if(strcmp(cmd_list[i],"<")==0) 
        {//存在输入重定向
			flag[pipe_num][0]=1;
			file[pipe_num][0]=cmd_list[i+1];
			argv[pipe_num][a++]=NULL;
		}
		else if(strcmp(cmd_list[i],">")==0)
         {//没有管道时的输出重定向
			flag[pipe_num][1]=1;
			file[pipe_num][1]=cmd_list[i+1];
			argv[pipe_num][a++]=NULL;//考虑有咩有输入重定向的情况
		}
        else 
            argv[pipe_num][a++]=cmd_list[i];
	}
}

//创建子进程，执行命令
int do_cmd() 
{
	pid=fork();//创建的子进程
	if(pid<0)
    {
		perror("fork error\n");
        exit(0);
	}
	//先判断是否存在管道，如果有管道，则需要用多个命令参数，并且创建新的子进程。否则一个命令即可
	else if(pid==0)
     {
		if(!pipe_num) 
        {//没有管道
			if(flag[0][0]) 
            {//判断有无输入重定向
				close(0);
				int fd=open(file[0][0],O_RDONLY);
			}
			if(flag[0][1]) 
            {//判断有无输出重定向
				close(1);
				int fd2=open(file[0][1],O_WRONLY|O_CREAT|O_TRUNC,0666);
			}
printf("execvp%s,%s\n",argv[0][0],argv[0][1]);
			execvp(argv[0][0],argv[0]);
		}
		else {//有管道
            int tt;//记录当前遍历到第几个命令
			for(tt=0;tt<pipe_num;tt++) 
            {
				int pid2=fork();
				if(pid2<0)
                {
					perror("fork error\n");
					exit(0);
				}
				else if(pid2==0) 
                {
					if(tt) 
                    {//如果不是第一个命令，则需要从共享文件读取数据
                        close(0);
					    int fd=open(pipe_file,O_RDONLY);//输入重定向
                    }
                    if(flag[tt][0]) 
                    {
						close(0);
						int fd=open(file[tt][0],O_RDONLY);
					}
					if(flag[tt][1]) 
                    {
						close(1);
						int fd=open(file[tt][1],O_WRONLY|O_CREAT|O_TRUNC,0666);
					}		
                    close(1);
                    remove(pipe_file);//由于当前f文件正在open中，会等到解引用后才删除文件
                    int fd=open(pipe_file,O_WRONLY|O_CREAT|O_TRUNC,0666);
					if(execvp(argv[tt][0],argv[tt])==-1) 
                    {
                        perror("execvp error!\n");
                        exit(0);
                    }
				}
				else {//管道后的命令需要使用管道前命令的结果，因此需要等待
					waitpid(pid2,NULL,0);
				}
			}
            //接下来需要执行管道的最后一条命令
			close(0);
			int fd=open(pipe_file,O_RDONLY);//输入重定向
			if(flag[tt][1]) 
            {
				close(1);
				int fd=open(file[tt][1],O_WRONLY|O_CREAT|O_TRUNC,0666);
			}
			execvp(argv[tt][0],argv[tt]);
		}
	}
	//father
	else 
    {
		waitpid(pid,NULL,0);
	}
	return 1;
}

int main(int argc,char** argv)
{
    
    background=0; //默认不在后台运行
    //循环读取和执行用户输入的命令
    while(1)
    {
        //将buf,cmd_num和cmd_list全部重置为0，确保每次用户输入的命令正常运行
        memset(buf,0,256);
        cmd_num = 0;
        for(int i = 0; i<100; i++)
            memset(cmd_list[i],0,256);
        if(one == 0)
        {
            printf("my_shell已运行\n");
            one++;
        }
        printf_hand();  //打印导航栏和当前工作目录
        get_input(); //获取用户的输入
        //如果输入的时exit就终止循环退出shell
        if( strcmp(buf,"exit") == 0 || strcmp(buf,"logout") == 0)
        {
            printf("my_shell已终止\n");
            break;
        }
        cut_input(); //按空格切割用户的输入，得到cmd_num和cmd_list
        //是否有cd命令
        if(strcmp(cmd_list[0],"cd") == 0)
        {
            if(my_cd(cmd_list[1]))
            {
                char tmp_file[256];
                getcwd(tmp_file,256);
                continue;
            }
            else
            {
                printf("param error!\n");
                continue;
            }
        }
        analazy_command();
        do_cmd();  //执行用户输入的命令
    }
}