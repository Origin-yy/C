#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<ctype.h>
#include<stdlib.h>
#include<wait.h>
#include<string.h>
#include<signal.h>
#include<dirent.h>

char his_workpath[100][256] = {'\0'};   //记录历史工作目录
int h = 0;                    //历史工作目录下标
int cmd_num = 0;              //按空格切割后的命令个数
char buf[1024] = {0};         //存储用户的输入（未解析的字符串）
char cmd_list[100][256] = {0};//按空格切割后的命令列表
int pid = 0;                  //存储子进程的进程号
char *pipe_file = "temp.txt"; //用做管道的文件
int flag[100][3] = {0};       //输入/输出/追加重定向标记。flag[i]表示以管道分割的第i个命令行，flag[i][0~1]表示是否有输入/追加/输出重定向(值为0表示无，1表示有)
char *file[100][3] = {0};     //输入/输出重定向的目标文件
char *argv[100][100] = {0};   //三维数组，每一个二维数组代表一个可执行程序的参数列表
int pipe_num = 0;             //管道个数
int background = 0;           //判断是否为有后台运行
int one = 0;                  //保证“my_shell已运行”只提示一次

//实现cd命令的函数
int my_cd(char *buf);
//打印导航栏的函数
void printf_hand();
//获取用户输入的函数
void get_input();
//按空格切割用户输入的函数
void cut_input();
//解析命令中的管道，重定向等信息的函数
void analysis_command();
//创建子进程，执行命令的函数
int do_cmd();
//查找可执行命令的函数
int find_cmd(char *command);


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
        analysis_command();
        do_cmd();  //执行用户输入的命令
    }
}


//实现cd命令的函数
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
}
//按空格切割用户输入的函数
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
//解析命令中的管道，重定向等信息的函数
void analysis_command() 
{
	//管道个数,管道的输入/输出/追加重定向标记和参数数组初始化为0
    pipe_num = 0;
	for(int i=0;i<100;i++)
    {
		flag[i][0] = flag[i][1] = flag[i][2] = 0;
		file[i][0] = file[i][1] = file[i][2] = 0;
		for(int j=0;j<100;j++)
			argv[i][j]=0;
	}

	for(int i=0; i<cmd_num; i++) 
        argv[0][i] = cmd_list[i];//初始化第一个参数数组
	argv[0][cmd_num] = NULL;     //参数数组最后一个元素为NULL
	int a = 0;    //当前命令参数的序号

	for(int i=0; i<cmd_num; i++) 
    {
		if(strcmp(cmd_list[i],"|") == 0) 
        {
			argv[pipe_num][a++] = NULL;
			pipe_num++;
			a = 0;
		}
		else if(strcmp(cmd_list[i],"<") == 0) 
        {
			flag[pipe_num][0] = 1;
			file[pipe_num][0] = cmd_list[i+1];
			argv[pipe_num][a++] = NULL;
		}
		else if(strcmp(cmd_list[i],">") == 0)
         {
			flag[pipe_num][1] = 1;
			file[pipe_num][1] = cmd_list[i+1];
			argv[pipe_num][a++] = NULL;
		}
        else if(strcmp(cmd_list[i],">>") == 0)
         {
			flag[pipe_num][2] = 1;
			file[pipe_num][2] = cmd_list[i+1];
			argv[pipe_num][a++] = NULL;
		}
        else 
            argv[pipe_num][a++] = cmd_list[i];
	}
}
//创建子进程，执行命令的函数
int do_cmd() 
{
	pid = fork();
	if(pid<0)
    {
		perror("fork error!\n");
        exit(0);
	}
    //子进程执行命令
	if(pid == 0)
    {
		if(pipe_num == 0)//如果没有管道，说明只有一个命令行
        {
			if(flag[0][0])
            {
				close(0);
				int fd = open(file[0][0],O_RDONLY);
			}
			if(flag[0][1])
            {
				close(1);
				int fd2 = open(file[0][1],O_WRONLY|O_CREAT|O_TRUNC,0666);
			}
            if(flag[0][2])
            {
				close(1);
				int fd3 = open(file[0][2],O_WRONLY|O_CREAT|O_APPEND,0644);
			}
            if( !(find_cmd(argv[0][0])) )
            {
                printf("未找到该命令：%s\n", argv[0][0]);
                exit(0);
            }
			execvp(argv[0][0],argv[0]);
		}
		else //有管道
        {
            int t;    //执行第t个管道前的命令行（t从零开始），最后一个管道后的命令行不会执行
			for(t=0; t<pipe_num; t++) 
            {
				int pid2 = fork();
				if(pid2<0)
                {
					perror("fork error!\n");
					exit(0);
				}
				else if(pid2==0) //孙进程运行
                {
					if(t) //如果不是第一个命令行（0），则需要从共享文件处读取数据
                    {
                        close(0);
					    int fd = open(pipe_file,O_RDONLY);
                    }
                    if(flag[t][0])
                    {
						close(0);
						int fd = open(file[t][0],O_RDONLY);
					}
					if(flag[t][1]) 
                    {
						close(1);
						int fd = open(file[t][1],O_WRONLY|O_CREAT|O_TRUNC,0666);
					}
                    if(flag[t][2])
                    {
						close(1);
						int fd = open(file[t][1],O_WRONLY|O_CREAT|O_APPEND,0644);
					}			
                    close(1);
                    remove(pipe_file);//由于当前pipe_file文件正在打开中（保存着最后一个管道前命令行的输出，会用作最后一个管道后命令行的输入），会等到使用后毕才删除文件
                    int fd = open(pipe_file,O_WRONLY|O_CREAT|O_TRUNC,0666);
                    if( !(find_cmd(argv[t][0])) )
                    {
                        printf("未找到该命令：%s\n", argv[0][0]);
                        exit(0);
                    }
					if(execvp(argv[t][0],argv[t]) == -1) 
                    {
                        perror("execvp error!\n");
                        exit(0);
                    }
				}
				else   //由于管道后的命令需要使用管道前命令的输出作为输入，因此子进程需要等待孙进程结束
					waitpid(pid2,NULL,0);
			}
            //执行最后一个管道后的命令（最后的命令）
			close(0);
			int fd = open(pipe_file,O_RDONLY);//输入重定向
			if(flag[t][1])
            {
				close(1);
				int fd = open(file[t][1],O_WRONLY|O_CREAT|O_TRUNC,0666);
			}
            else if(flag[t][2])
            {
                close(1);
				int fd = open(file[t][2],O_WRONLY|O_CREAT|O_APPEND,0644);
            }
            if( !(find_cmd(argv[t][0])) )
            {
                printf("未找到该命令：%s\n", argv[0][0]);
                exit(0);
            }
			execvp(argv[t][0],argv[t]);
		}
	}
	else //父进程等待子进程结束 
		waitpid(pid,NULL,0);
	return 1;
}
//查找可执行命令的函数
int find_cmd(char *command)
{
    DIR* dp;
    struct dirent* dirp;
    char* path[] = {"./", "/bin","/usr/bin",NULL};
    //使当前目录下的程序可以运行，如命令“./fork”可以被正确解释和执行
    if( strncmp(command, "./", 2) == 0 )
        command = command + 2;
    //分别在当前目录，/bin和/usr/bin目录查找要执行的程序
    int i = 0;
    while(path[i] != NULL)
    {
        if( (dp = opendir(path[i])) == NULL )
            printf("my_shell:can't open /bin \n");
        while( (dirp = readdir(dp)) != NULL )
            if(strcmp(dirp->d_name, command) == 0)
            {
                closedir(dp);
                return 1;
            }
        closedir(dp);
        i++;
    }
    return 0;
}