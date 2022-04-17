#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<dirent.h>
#include<signal.h>

#define normal    0   //普通命令
#define out_r     1   //输出重定向
#define in_r      2   //输入重定向
#define have_pipe 3   //命令中有管道
#define out_a_r   4   //输出追加重定向

int background = 0;   //判断是否在后台运行
char his_workpath[100][256] = {'\0'};   //记录历史工作目录
int h = 0;             //历史工作目录下标

//实现cd命令的实函数
int my_cd(char *buf);
//打印导航栏和当前工作目录的函数
void printf_hand();
//获取用户输入的函数
void get_input(char* buf);
//解析用户输入的函数
void parse_input(char *buf,int* cmd_num,char cmd_list[100][256]);
//查找可执行命令的函数
int find_cmd(char *command);
//执行命令的函数
void do_cmd(int cmd_num,char cmd_list[100][256]);

int main(int argc,char** argv)
{
    char* buf = NULL;         //用来保存用户输入的未解析的一或多个命令
    int cmd_num = 0;          //用来保存解析后的命令个数    
    char cmd_list[100][256];   //用数组来保存解析后的命令列表(最多10个命令，一个命令的长度最长为256)

    buf = (char*)malloc(256);
    if(buf  == NULL)
    {
        perror("malloc failed");
        exit(-1);
    }
    background=0; //默认不在后台运行
    //循环读取和执行用户输入的命令
    while(1)
    {
        //将buf,cmd_num和cmd_list全部重置为0，确保每次用户输入的命令正常运行
        memset(buf,0,256);
        cmd_num = 0;
        for(int i = 0; i<100; i++)
            memset(cmd_list[i],0,256);
        printf("my_shell已运行\n");
        printf_hand();  //打印导航栏和当前工作目录
        get_input(buf); //获取用户的输入
        //如果输入的时exit就终止循环退出shell
        if( strcmp(buf,"exit") == 0 || strcmp(buf,"logout") == 0)
        {
            printf("my_shell已终止\n");
            break;
        }
        parse_input(buf,&cmd_num,cmd_list); //解析用户的输入，得到cmd_num和cmd_list
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
        do_cmd(cmd_num,cmd_list);  //执行用户输入的命令
    }
    if(buf != NULL)
    {
        free(buf);
        buf = NULL;
    }
    return 0;
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
//获取用户输入的函数
void get_input(char* buf)
{
    int len = 0;    //保存用户输入的长度
    char ch;    
    //逐个字符读取，当读到回车时停止(未读入\n)
    ch = getchar();
    while (len < 256 && ch != '\n')
    {
        buf[len++] = ch;
        ch = getchar();
    }
    //用户输入不可以超过256个字符
    if(len == 256)
    {
        perror("command is too long\n");
        exit(-1);
    }
    //在结尾手动填上\0
    buf[len] = '\0';
}
//解析用户输入的函数
void parse_input(char *buf,int* cmd_num,char cmd_list[100][256])
{
    //解析出每一个命令（空格分割）
    char *ptr;
    char *old;
    ptr = strtok_r(buf," ",&old);
    while(ptr != NULL)
    {
        strcpy(cmd_list[*cmd_num],ptr) == NULL;
        *cmd_num += 1;
        ptr = strtok_r(NULL," ",&old);
        if(*cmd_num > 99)
           printf("命令太多了\n");
    }
}
//查找可执行命令的函数
int find_cmd(char *command)
{
    DIR* dp;
    struct dirent* dirp;
    char* path[] = {"./", "/bin", "/usr/bin", NULL};

    //使当前目录下的程序可以运行，如命令“./fork”可以被正确解释和执行
    if( strncmp(command, "./", 2) == 0 )
    {
        command = command + 2;
    }

    //分别在当前目录，/bin和/usr/bin目录查找要执行的程序
    int i = 0;
    while(path[i] != NULL)
    {
        if( (dp = opendir(path[i])) == NULL )
        {
            printf("can not open /bin \n");
        }
        while( (dirp = readdir(dp)) != NULL )
        {
            if(strcmp(dirp->d_name, command) == 0)
            {
                closedir(dp);
                return 1;
            }
        }
        closedir(dp);
        i++;
    }
    return 0;
}
//执行命令的函数
void do_cmd(int cmd_num,char cmd_list[10][256])
{
    int flag = 0;       //标记命令行是否正确（只有一个<或>或|，1且格式正确）
    int how = 0;        //用于标识命令中是否含有输出重定向> ,输入重定向< , 管道 |
    int background = 0; //标识命令中是否有后台运行的标示符
    int status;         //保存子函数的返回状态
    int fd;             //重定向时保存目标文件的文件描述符，将这个文件作为标准输出/标准输入
    char* arg[cmd_num + 1];     //有管道时保存第一个命令
    char* argnext[cmd_num + 1]; //有管道时保存第二个命令
    char* file;                 //重定向时用到的的文件名
    pid_t pid;                  //子进程的pid

    //将命令取出
    for(int i = 0; i < cmd_num; i++)
       arg[i] = (char *)cmd_list[i];
    arg[cmd_num] = NULL;

    //查找是否输入后台运行符&
    for(int i = 0; i < cmd_num; i++)
    {
        if(strncmp(arg[i],"&",1) == 0)
        {
            if(i == cmd_num - 1) //如果&是最后一个命令，则后台运行
            {
                background = 1;
                arg[cmd_num - 1] = NULL;
                break;
            }
            else                 //否则&不是最后一个命令，输入错误，报错返回
            {
                printf("'&'应放在最后\n");
                return ;
            }
        }
    }
    //查找含有有输出重定向>, 输入重定向<, 管道|中的哪一个
    for(int i=0; arg[i] != NULL; i++)
    {
        if(strcmp(arg[i], ">") == 0)
        {
            flag++;
            how = out_r;
                if(arg[i + 1] == NULL)
                    flag++;
        }
        if(strcmp(arg[i], ">>") == 0)
        {
            flag++;
            how = out_a_r;
                if(arg[i + 1] == NULL)
                    flag++;
        }
        if(strcmp(arg[i], "<") == 0)
        {
            flag++;
            how = in_r;
            if(i == 0)  flag++;
        }
        if(strcmp(arg[i], "|") == 0)
        {
            flag++;
            how = have_pipe;
            if(arg[i + 1] == NULL)
                flag++;
            if(i == 0)
                flag++;
        }
    }

    //若flag大于1，说明有<，>，|的组合，或者命令的格式不对，报错返回
    if(flag > 1)
    {
        printf("存在<,>,|的组合或命令格式错误\n");
        return;
    }
    if(how == out_r)
    {
        //命令只含有一个输出重定向符号
        for(int i=0; arg[i] != NULL; i++)
        {
            if(strcmp(arg[i], ">") == 0)
            {
                file = arg[i + 1];
                arg[i] = NULL;
            }
        }
    }
    if(how == out_a_r)
    {
        //命令含有输出追加重定向符号
        for(int i = 0; arg[i] != NULL; i++)
        {
            if(strcmp(arg[i], ">>") == 0)
            {
                    file = arg[i + 1];
                    arg[i] = NULL;
            }
        }
    }
    if(how == in_r)
    {
        //命令只含有一个输入重定向
        for(int i = 0; arg[i] != NULL; i++)
        {
            if(strcmp(arg[i], "<") == 0)
            {
                file = arg[i + 1];
                arg[i] = NULL;
            }
        }
    }

    if(how == have_pipe)
    {
        //命令只有一个管道符号，把管道符后面的部分存入argnext中，管道后面的部分是一个可执行的shell命令
        for(int i=0; arg[i] != NULL; i++)
        {
            if(strcmp(arg[i], "|") == 0)
            {
                arg[i] = NULL;
                int j;
                //把管道符后面的部分存入argnext中
                for(j = i+1; arg[j] != NULL; j++)
                {
                    argnext[j-i-1] = arg[j];
                }
                argnext[j-i-1] = arg[j];
                break;
            }
        }
    }
    if((pid = fork()) < 0)
    {
        printf("fork error\n");
        return ;
    }
    //父子进程进行不同的操作
    switch(how)
    {
    case 0:
        //输入的命令中不含>，<，|，pid为0说明是子进程，在子进程中执行输入的命令
        if(pid == 0)
        {
            if(!(find_cmd(arg[0])))
            {
                printf("%s : command not found\n", arg[0]);
                exit(0);
            }
            execvp(arg[0], arg);//调用execvp执行命令
            exit(0);
        }
        break;

    case 1:
        //输入的命令中含有输出重定向符>，pid为0说明是子进程，在子进程中执行输入的命令
        if(pid == 0)
        {
            if( !(find_cmd(arg[0])) )
            {
                printf("%s : command not found\n", arg[0]);
                exit(0);
            }
            fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
            //把标准输入获得的内容写到fd指向的file文件里
            dup2(fd, 1);
            execvp(arg[0], arg);//调用execvp执行命令
            exit(0);
        }
        break;

    case 2:
        //输入的命令中含有输入重定向<，pid为0说明是子进程，在子进程中执行输入的命令
        if(pid == 0)
        {
            if( !(find_cmd (arg[0])) )
            {
                printf("%s : command not found\n", arg[0]);
                exit(0);
            }
            fd = open(file, O_RDONLY);
            //把文件中的内容作为标准输入给程序
            dup2(fd, 0);
            execvp(arg[0], arg);//调用execvp执行命令
            exit(0);
        }
        break;

    case 3:
        //输入的命令中含有管道符|，pid为0说明是子进程，在子进程中执行输入的命令
        if(pid == 0)
        {
            int pid2;    //孙进程的pid
            int status2; //孙进程的结束状态
            int fd2;     //孙进程临时文件的文件描述符，用于进程间的通信

            //子进程再fork, 再创建一个子进程
            if( (pid2 = fork()) < 0 )
            {
                printf("fork error\n");
                return ;
            }
            else if(pid2 == 0)
            {
                if( !(find_cmd(arg[0])) )
                {
                    printf("%s : command not found\n", arg[0]);
                    exit(0);
                }
                fd2 = open("/temp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
                dup2(fd2, 1);
                execvp(arg[0], arg);
                exit(0);
            }
            if(waitpid(pid2, &status2, 0) == -1)
            {
                printf("wait for child process error\n");
            }
            if( !(find_cmd(argnext[0])) )
            {
                printf("%s : command not found\n", argnext[0]);
                exit(0);
            }
            fd2 = open("/temp", O_RDONLY);
            dup2(fd2, 0);
            execvp (argnext[0], argnext);
            //如果删除成功，remove返回0，否则返回EOF（-1）。
            if( remove("/temp") == -1 )
            {
                printf("remove error\n");
            }
            exit(0);
        }
        break;
    case 4:
        //输入的命令中含有输出追加重定向符>>，pid为0说明是子进程，在子进程中执行输入的命令
        if(pid == 0)
        {
            if( !(find_cmd(arg[0])) )
            {
                printf("%s : command not found\n", arg[0]);
                exit(0);
            }
            close(1);
            fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
            execvp(arg[0], arg);
            close(fd);
            exit(0);
        }
        break;

    default:
        break;
    }

    //若命令中有&，表示后台执行，父进程直接返回，不等待子进程结束
    if(background == 1)
    {
        printf("process id %d \n", pid);
        return ;
    }

    //父进程等待子进程结束
    if(waitpid(pid, &status, 0) == -1)
    {
        printf("wait for child process error\n");
    }
}
