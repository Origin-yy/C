#include<stdio.h>
#include<stdlib.h>    //malloc
#include<string.h>    //字符串处理函数
#include<sys/stat.h>  //lstat，S_ISDIR等宏
#include<sys/types.h> //lstat,opendir，getpwuid，getgrgid
#include<time.h>
#include<unistd.h>    //lstat
#include<dirent.h>    //opendir,readdir
#include<grp.h>
#include<pwd.h>       //getpwuid，getgrgid
#include<errno.h>

#define NO 0      //无参数
#define A 1       //-a：显示所有文件
#define L 2       //-l：显示文件的详细信息
#define R 4       //-R：连同子目录内容一起列出来
#define I 2       //-i：显示每个文件的inode号
#define T 8       //-t：按文件创建时间排序
#define r 16      //-r：将文件以相反次序显示
#define S 64      //-s：按文件大小排序显示

#define NORMAL 0
#define GREEN  1 
#define BLUE   2
#define S_BLUE 3
#define YELLOW 4



#define  MAX_ROWLEN 100   //一行显示的最多字符串

int g_leave_len = MAX_ROWLEN;    //一行剩余长度，用于输出对亲
int g_maxlen;                   //存放某目录下最长文件名的长度

int flag = 0;         //记录所有参数
char path[260];       //记录路径名
char param[8] = {'0'};//记录有哪些参数
int n = 0;            //记录参数个数
int Index[100000];    //记录filenames下标

//分析参数，得到flag，path，buf，n，param[]
void anal_param(int argc,char *argv[]);
//错误处理函数
void my_err(const char *err_string, int line);
//“路径是文件”打印函数
void disply_file(char *filename);
//“路径是目录”打印函数
void displt_dir(char *dirname);

int main (int argc,char* argv[])
{
    anal_param(argc,argv);          //解析参数和判断是否含有有效路径

    //根据路径类型进入不同函数 
    int i = 1;
    struct stat buf;
    do{
        if(S_ISDIR(buf.st_mode))    //如果输入的路径是目录，进入“打印目录”函数
        {
            display_dir(flag,path);
            i++;
        }
        else                        //否则输入的路径是文件，进入“打印文件”函数                  
        {
            display_file(flag,path);
            i++;
        }
    }while(i < argc);
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
    int i = 1;
    struct stat buf;                //用stat结构体保存输入的路径的信息，用以检验路径是否存在
    do{   
        if(argv[i][0] == '-')       //如果是参数就跳过，否则（是路径）就保存该路径
        {
            i++;
                    continue;
        }
        else
            strcpy(path,argv[i]);
        if(lstat(path,&buf) == -1)   //如果输入的路径不存在，传到错误函数，报错并退出
            my_err("lstat",__LINE__);
    }while(i<argc);
}
//错误处理函数
void my_err(const char *err_string, int line)
{
    fprintf(stderr,"line: %d ",line);
    perror(err_string);
    exit(1);
}
//染色函数
void color(char *name, struct stat buf)
{
    if(S_ISDIR(buf.st_mode))    //目录
        printf("\e[1;34m%-s\e[0m",name);
    else if(S_ISDIR(buf.st_mode) && (buf.st_mode & 0777) == 0777)   //满权限目录
        printf("\e[1;34;42m%-s\e[0m",name);
    else if(S_ISLNK(buf.st_mode))   //符号链接
        printf("\e[1;36m%-s\e[0m",name);
    else if(buf.st_mode & S_IXUSR || buf.st_mode & S_IXGRP || buf.st_mode & S_IXOTH)    //可执行文件
        printf("\e[1;32m%-s\e[0m",name);
    else
        printf("%-s",name);
}
//“路径是文件”打印函数（只需考虑参数l,i）
void disply_file(char *filename)
{
    if(flag & L)     //有-l参数
    {
        struct stat buf;        //保存文件信息
        char buf_time[32];      //保存时间
        struct passwd *psd;     //从passwd结构体获取用户名
        struct group *grp;      //从group结构体获取所属组名

        if(lstat(filename,&buf) == -1)  //获取文件信息
            my_err("lstat",__LINE__);

        if(flag & I)                    //有参数i就打印inode号  
            printf("%ld ",buf.st_ino);

        //获取并打印文件类型
        if(S_ISLNK(buf.st_mode)){           //符号链接
            printf("l");            
        } else if(S_ISREG(buf.st_mode)){    //一般文件
            printf("-");
        } else if(S_ISDIR(buf.st_mode)){    //目录文件
            printf("d");
        } else if(S_ISCHR(buf.st_mode)){    //字符设备文件
            printf("c");
        } else if(S_ISBLK(buf.st_mode)){    //块设备文件
            printf("b");
        } else if(S_ISFIFO(buf.st_mode)){   //先进先出文件
            printf("f");
        } else if(S_ISSOCK(buf.st_mode)){   //socket
            printf("s");
        }

        //获取并打印拥有者权限
        if(buf.st_mode & S_IRUSR)   
            printf("r");
        else 
            printf("-");
        if(buf.st_mode & S_IWUSR)
            printf("w");
        else 
            printf("-");

        if(buf.st_mode & S_IXUSR)
            printf("x");
        else 
            printf("-");

        //获取并打印组权限   
        if(buf.st_mode & S_IRGRP)
            printf("r");
        else 
            printf("-");

        if(buf.st_mode & S_IWGRP)
            printf("w");
        else 
            printf("-");

        if(buf.st_mode & S_IXGRP)
            printf("x");
        else 
            printf("-");


        //获取并打印其他用户权限
        if(buf.st_mode & S_IROTH)
            printf("r");
        else 
            printf("-");

        if(buf.st_mode & S_IWOTH)
            printf("w");
        else 
            printf("-");

        if(buf.st_mode & S_IXOTH)
            printf("x");
        else 
            printf("-");

        printf("\t");   
        //通过stat结构体里的uid和gid得到存有用户名和组名的passwd和group结构体
        psd = getpwuid(buf.st_uid);
        grp = getgrgid(buf.st_gid);

        printf("%4ld ",buf.st_nlink);            //打印文件的硬链接数
        printf("%-8s  ",psd->pw_name);           //打印用户的名字
        printf("%-8s", grp->gr_name);            //打印用户组的名字

        printf("%6ld", buf.st_size);             //打印文件大小
        strcpy(buf_time,ctime(&buf.st_mtime));   //把时间转换成普通表示格式

        buf_time[strlen(buf_time)-1] = '\0';     //去掉换行符
        printf("  %s", buf_time);                //输出时间 

        color(filename,buf);                     //染色打印
        printf("\n");
    }
    else             //无-l参数
    {
        int i,len;
        struct stat buf;
        if(lstat(filename,&buf) == -1)
            my_err("lstat",__LINE__);

        //如果本行不足以打印一个文件名则换行
        if(g_leave_len < g_maxlen)
        {
            printf("\n");
            g_leave_len = MAX_ROWLEN;
        }

        if(flag & I)                    //有参数i就打印inode号  
            printf("%ld ",buf.st_ino);

        len = strlen(filename);
        len = g_maxlen - len;
        color(filename,buf);

        for(i = 0; i < len; i++)
            printf(" ");
        printf("  ");               //多打两个空格
        g_leave_len -= (g_maxlen + 2);
    }
}
//“路径是目录”打印函数
void disply_dir(char *dirname)
{
    DIR *dir;
    struct dirent *ptr;
    int count = 0;      //该目录下文件总数
    int i,j,len;
    

    if((flag & R) != 0)
    {
        //要考虑全面一些
        len = strlen(path);
        if(len > 0)
        {
            if(path[len - 1] == '/')
                path[len - 1] = '\0';
        }
        if((dirname[0] == '.' || dirname[0] == '/') && flag == 0)
        {
            strcat(path,dirname);
            //flag++;
        }
        else
        {
            strcat(path,"/");
            strcat(path,dirname);
        }
        printf("%s:\n",path);
    }

    
    //获取该目录下文件总数和最长文件名
    dir = opendir(dirname);
    if(dir == NULL)
        my_err("opendir",__LINE__);
    
    g_maxlen = 0;
    while((ptr = readdir(dir)) != NULL)
    {
        if(g_maxlen < strlen(ptr->d_name))
            g_maxlen = strlen(ptr->d_name);
        count++;
    }
    closedir(dir);
    
    //动态分配空间，减少栈的消耗
    char **filenames = (char **)malloc(sizeof(char *) * count);
    memset(filenames,0,sizeof(char *) * count);
    for(i = 0; i < count; i++)
    {
        filenames[i] = (char *)malloc(sizeof(char) * g_maxlen + 1);
        memset(filenames[i],0,sizeof(char) * g_maxlen + 1);
    }

    //获取该目录下所有文件名
    dir = opendir(dirname);
    len = strlen(dirname);
    for(i = 0; i < count; i++)
    {
        ptr = readdir(dir);
        if(ptr == NULL)
            my_err("readdir",__LINE__);
        strcpy(filenames[i],ptr->d_name);

        Index[i] = i;
    }
    closedir(dir);

    //切换工作目录
    if(chdir(path) < 0)
        my_err("chdir",__LINE__);

    display(filenames,count);

    
    //释放空间
    if(flag & R)
        free(filenames);
    else
    {
        for(i = 0; i < count; i++)
            free(filenames[i]);
        free(filenames);
    }

    if(!(flag & L) && !(flag & R))
        printf("\n");
}
