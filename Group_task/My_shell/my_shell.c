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

//打印导航栏和当前工作目录的函数
void printf_hand();
//获取用户输入的函数
void get_input(char* buf);
//解析用户输入的函数
void parse_input(char *buf,int* cmd_num,char cmd_list[10][256]);
//执行命令的函数
void do_cmd(int cmd_num,char cmd_list[10][256]);

int main(int argc,char** argv)
{
    char* buf = NULL;         //用来保存用户输入的未解析的一或多个命令
    int cmd_num = 0;          //用来保存解析后的命令个数    
    char cmd_list[10][256];   //用数组来保存解析后的命令列表(最多10个命令，一个命令的长度最长为256)

    buf = (char*)malloc(256);
    if(buf  == NULL)
    {
        perror("malloc failed");
        exit(-1);
    }

    while(1)
    {
        printf_hand();  //打印导航栏和当前工作目录
        get_input(buf); //获取用户的输入

        //将buf,cmd_num和cmd_list全部重置为0，确保每次用户输入的命令正常运行
        memset(buf,0,256);
        cmd_num = 0;
        for(int i = 0; i<10; i++)
            memset(cmd_list[i],0,256);

        
        //如果输入的时exit就终止循环退出shell
        if( strncmp(buf,"exit\n",5) == 0 )
            break;
        
        parse_input(buf,&cmd_num,cmd_list); //解析用户的输入，得到cmd_num和cmd_list
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
    char *hand2 = NULL;                //保存当前工作目录
    hand2 = getcwd(NULL,0);
    printf("\e[1;32m%-s\e[0m:\e[1;34m%-s\e[0m",hand1,hand2);

    free(hand2);
}
//获取用户输入的函数
void get_input(char* buf)
{
    int len = 0;    //保存用户输入的长度
    char ch = '\0';    

    //逐个字符读取，当读到回车时停止(未读入\n)
    ch = getchar();
    while (len < 256 && ch != '\n')
    {
        buf[len++] = getchar();
        ch = getchar();
    }
    //用户输入不可以超过256个字符
    if(len == 256)
    {
        perror("command is too long\n");
        exit(-1);
    }
    //在结尾手动填上\n和\0
    buf[len] = '\n';
    buf[len+1] = '\0';
}
//解析用户输入的函数
void parse_input(char *buf,int* cmd_num,char cmd_list[10][256])
{
    //把用户输入按空格分割成多个字符串，保存进cmd_list
    char *begin = buf;   //一个参数的开头
    char *end = buf;     //一个参数的结尾
    int number = 0;      //一个参数的字符数
    //判断是否在后台运行
    for (int i=0; i<strlen(buf); i++)
        if(buf[i] == '#')
            background = 1;
    while(1)
    {
        if(begin[0]=='\0')
            break;
        if(begin[0]==' ')
            begin++;
        else
        {
            end = begin;
            number = 0;
            while(end[0] !='\n' && end[0] != ' ')
            {
                number++;
                end++;
            }
            strncpy(cmd_list[*cmd_num],begin,number+1);
        }


    }


}
//执行命令的函数
void do_cmd(int cmd_num,char cmd_list[10][256])
{

}