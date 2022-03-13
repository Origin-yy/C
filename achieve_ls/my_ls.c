#include<stdio.h>
#include<stdlib.h>    //malloc
#include<string.h>    //字符串处理函数
#include<sys/stat.h>  //lstat，S_ISDIR
#include<sys/types.h> //lstat,opendir
#include<time.h>
#include<unistd.h>    //lstat
#include<dirent.h>    //opendir,readdir
#include<grp.h>
#include<pwd.h>
#include<errno.h>

#define NO 0    //无参数
#define A 1       //-a：显示所有文件
#define L 2       //-l：显示文件的详细信息
#define R 4       //-R：连同子目录内容一起列出来
#define T 8       //-t：按文件创建时间排序
#define r 16      //-r：将文件以相反次序显示
#define I 32      //-i：显示每个文件的inode号
#define S 64      //-s：按文件大小排序显示
#define max_rowline 100   //一行显示的最多字符串

int flag = 0;         //记录所有参数
char path[260];       //记录路径名
struct stat buf;      //用stat结构体保存输入的路径的信息
char param[8] = {'0'};//记录有哪些参数
int n = 0;            //记录参数个数

//分析参数，得到flag，path，buf，n，param[]
void anal_param(int argc,char *argv[]);

//错误处理函数
void my_err(const char *err_string, int line);

int main (int argc,char* argv[])
{
    anal_param(argc,argv);

    for(int i = 1;i++;i < argc)     //根据路径类型进入不同函数
    {
        if(S_ISDIR(buf.st_mode))    //如果输入的路径是目录，进入“打印目录”函数
            {
                display_dir(path);
                i++;
            }
            else                    //否则输入的路径是文件，再判断
            {
                if(flag & L)        //如果含有-l参数，进入“按-l参数打印文件”函数
                   display_l(path);
                else                //否则，进入“仅仅打印文件名”函数
                {
                   display_single(path);
                   printf("\n");
                }
                i++;
            }
    }


    return 0;
}


//分析参数函数
void anal_param(int argc,char *argv[])
{
    //保存参数进param
    for(int i =  1; i < argc; i++)
    {
        if(argv[i][0] == '-')
        {
            param[i-1] = argv[i][1];  //获取‘-’后的参数保存到数组param中
            n++;
        }
    }
    //将参数保存在flag中
    for(int i = 0; i < n; i++)
    {
        if(param[i] == 'a')
        {  
            flag |= A;
            continue;
        }
        else if(param[i] == 'l')
        {
            flag |= L;
            continue;
        }
        else if(param[i] == 'R')
        {
            flag |= R;
            continue;
        }
        else if(param[i] == 't')
        {
            flag |= T;
            continue;
        }
        else if(param[i] == 'r')
        {
            flag |= R;
            continue;
        }
        else if(param[i] == 'i')
        {
            flag |= I;
            continue;
        }
        else if(param[i] == 's')
        {
            flag |= S;
            continue;
        }
        else
        {
            printf("my_ls: 无法实现参数： -%c\n",param[i]);
            exit(1);
        }
    }
    //如果没有输入文件（目录）路径，用path保存当前路径
    if((n + 1) == argc)
    {
        strcpy(path,".");
    }
    //查找并保存输入的文件（目录）路径，检验有效后，用path保存该路径
    for(int i = 1;i++;i < argc)
    {   
        if(argv[i][0] == '-')       //如果是参数就跳过，否则（是路径）就保存该路径
        {
            i++;
            continue;
        }
        else
            strcpy(path,argv[i]);
        if(lstat(path,&buf) == -1)   //如果输入的路径不存在，传到错误函数，报错并退出
            my_err("lstat",__LINE__);
    }
}
//错误处理函数
void my_err(const char *err_string, int line)
{
    fprintf(stderr,"line: %d ",line);
    perror(err_string);
    exit(1);
}

