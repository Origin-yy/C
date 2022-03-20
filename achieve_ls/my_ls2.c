# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <sys/stat.h>
# include <unistd.h>
# include <sys/types.h>
# include <limits.h>
# include <dirent.h>
# include <grp.h>
# include <pwd.h>
# include <errno.h>
# include <signal.h>

#define PARAM_NONE 0      //无参数
#define PARAM_A 1       //-a：显示所有文件
#define PARAM_L 2       //-l：显示文件的详细信息
#define PARAM_R 4       //-R：连同子目录内容一起列出来
#define PARAM_I 8       //-i：显示每个文件的inode号
#define PARAM_T 16       //-t：按文件创建时间排序
#define PARAM_S 32      //-s：按文件大小排序显示
#define PARAM_r 64      //-r：将文件以相反次序显示
#define MAXROWLEN 80    // 一行显示的最多字符数

int flag_param = PARAM_NONE;
int  g_leave_len = MAXROWLEN;    // 一行剩余长度，用于输出对齐
int g_maxlen;                    // 存放某目录下最长文件名的长度

// 错误处理函数，打印出错误所在行的行数和错误信息
void my_err(const char *err_string,int line)
{
    fprintf(stderr,"line:%d",line);      //stderr：标准错误输出设备(默认向屏幕输出)
    perror(err_string);                                                      
    exit(1);
}

// 获取文件属性并打印
void display_attribute(struct stat buf, char * name) 
{
    char buf_time[32];
    struct passwd *psd;    //从该结构体中获取文件所有者的用户名
    struct group *grp;     //从该结构体中获取文件所有者所属组的组名

    //获取文件属性并打印
    if (S_ISLNK(buf.st_mode)) {
        printf("l");
    } else if (S_ISREG(buf.st_mode)) {
        printf("-");
    } else if (S_ISDIR(buf.st_mode)) {
        printf("d");
    } else if (S_ISCHR(buf.st_mode)) {
        printf("c");
    } else if (S_ISBLK(buf.st_mode)) {
        printf("b");
    } else if (S_ISFIFO(buf.st_mode)) {
        printf("f");
    } else if (S_ISSOCK(buf.st_mode)) {
        printf("s");
    }

    //获取并打印文件所有者的权限
    if (buf.st_mode & S_IRUSR) {
        printf("r");
    } else {
        printf("-");
    }
    if (buf.st_mode & S_IWUSR) {
        printf("w");
    } else {
        printf("-");
    }
    if (buf.st_mode & S_IXUSR) {
        printf("x");
    } else {
        printf("-");
    }

    //获取并打印与文件所有者同组的用户对该文件的操作权限
    if (buf.st_mode & S_IRGRP) {
        printf("r");
    } else {
        printf("-");
    }
    if (buf.st_mode & S_IWGRP) {
        printf("w");
    } else {
        printf("-");
    }
    if (buf.st_mode & S_IXGRP) {
        printf("x");
    } else {
        printf("-");
    }

    //获取并打印其他用户对该文件的操作权限
    if (buf.st_mode & S_IROTH) {
        printf("r");
    } else {
        printf("-");
    }
    if (buf.st_mode & S_IWOTH) {
        printf("w");
    } else {
        printf("-");
    }
    if (buf.st_mode & S_IXOTH) {
        printf("x");
    } else {
        printf("-");
    }

    printf("    ");

    //根据 uid 与 gid 获取文件所有者的用户名与组名
    psd = getpwuid(buf.st_uid);
    grp = getgrgid(buf.st_gid);
    printf("%4ld ",buf.st_nlink);  //打印文件的链接数 
    printf("%-8s ",psd->pw_name);
    printf("%-8s ",grp->gr_name);

    printf("%6ld",buf.st_size);
    strcpy(buf_time, ctime(&buf.st_mtime));
    buf_time[strlen(buf_time) - 1] = '0';    // 去掉换行符
    printf(" %s",buf_time);    //打印文件的时间信息
}

// 在没有使用-1选项时，打印一个文件名，打印时上下行对齐
void display_single(char *name)
{
    int i, len;

    //如果本行不足以打印一个文件名则换行
    if (g_leave_len < g_maxlen) {
        printf("\n");
        g_leave_len = MAXROWLEN;
    }

    len = strlen(name);
    len = g_maxlen - len;
    printf("%-s",name);

    printf("  ");
    //下面的 2 指空两格
    g_leave_len -= (g_maxlen + 2);
}

void display_i(char *name)
{
    struct stat buf;

    if (lstat(name, &buf) == -1)
    {
        my_err("stat", __LINE__);
    }

    printf("%-9ld %s",buf.st_ino,name);
    printf("\n");
}

/*
*   根据命令行参数和完整路径名显示目标文件
*   参数flag：命令行参数
*   参数pathname：包含了文件名的路径名
*/
void display(char * pathname)
{
    int i, j;
    struct stat buf;
    char name[260];

    //从路径中解析出文件名
    for (i=0, j=0; i<strlen(pathname); i++) {
        if (pathname[i] == '/') {
            j = 0;
            continue;
        }
        name[j++] = pathname[i];
    }
    name[j] = '\0';

    //用 lstat 而不是 stat 以方便解析链接文件
    if ( lstat(pathname, &buf) == -1) {
        my_err("stat",__LINE__);
    }

    switch (flag_param) {
        case PARAM_NONE:  //没有选项
            if (name[0] != '.') {
                display_single(name);
            }
            break;
        
        case PARAM_A:  //-a: 显示包括隐藏文件在内的所有文件
            display_single(name);
            break;
        
        case PARAM_L:  //-l: 每个文件单独占一行，显示文件详细属性信息
            if (name[0] != '.') {
                display_attribute(buf, name);
                printf(" %-s\n",name);
            }
            break;
        
        case PARAM_A + PARAM_L:  //同时有-l和-a选项的情况
            display_attribute(buf, name);
            printf(" %-s\n",name);
            break;

        case PARAM_R:
            if(name[0] != '.') {
                display_single(name);
            }
            break;
        
        case PARAM_R + PARAM_A:
            display_single(name);
            break;
            
        case PARAM_A + PARAM_L + PARAM_R:
            display_attribute(buf,name);
            printf(" %-s\n",name);
            break;
            
        case PARAM_L + PARAM_R:
            if(name[0] != '.') {
                display_attribute(buf,name);
                printf(" %-s\n",name);
            }
            break;

        case PARAM_r:
            if(name[0] != '.') {
                display_single(name);
            }
        break;

        case PARAM_I:
            if(name[0] != '.') {
                display_i(name);
            }

        default:
            break;
    }
}

void display_dir(char *path)
{
    DIR *dir;
    struct dirent *ptr;                                                                      //struct dirent
    int count = 0;
    char filenames[256][260],temp[260];

    //获取该目录下文件总数和最长的文件名
    dir = opendir(path); 
    
    if (dir == NULL) {
        my_err("opendir",__LINE__);
    }

    while ((ptr = readdir(dir)) != NULL) {   // readdir()读取opendir 返回值的那个列表
        if (g_maxlen < strlen(ptr->d_name)) {
            g_maxlen = strlen(ptr->d_name);
        }
        count++;
    }
    closedir(dir);

    if(count>256)
        my_err("too many files under this dir",__LINE__);

    int i, j, len = strlen(path);
    
    //获取该目录下所有的文件名
    dir = opendir(path);
    
    for(i = 0; i < count; i++) {
        ptr = readdir(dir);
        if( ptr == NULL ) {
            my_err("readdir",__LINE__);
        }
        strncpy(filenames[i],path,len);
        filenames[i][len] = '\0';
        strcat(filenames[i],ptr->d_name);
        filenames[i][len+strlen(ptr->d_name)] = '\0';
    }

    //使用冒泡法对文件名进行排序，排序后文件名按字母顺序存储于filenames
    if(flag_param & PARAM_r) {
        for(i = 0; i < count - 1; i++) {
            for(j = 0; j < count - 1 - i; j++) {
                if(strcmp(filenames[j], filenames[j+1]) < 0) {
                    strcpy(temp, filenames[j + 1]);
                    temp[strlen(filenames[j+1])] = '\0';
                    strcpy(filenames[j+1], filenames[j]);
                    filenames[j+1][strlen(filenames[j])] = '\0';
                    strcpy(filenames[j], temp);
                    filenames[j][strlen(temp)] = '\0';
                }
            }
        }
    } else {
        for(i = 0; i < count-1; i++) {
            for(j = 0; j < count-1-i; j++) {
                if( strcmp(filenames[j],filenames[j+1]) > 0 ) {
                    strcpy(temp,filenames[j+1]);
                    temp[strlen(filenames[j+1])] = '\0';
                    strcpy(filenames[j+1],filenames[j]);
                    filenames[j+1][strlen(filenames[j])] = '\0';
                    strcpy(filenames[j],temp);
                    filenames[j][strlen(temp)] = '\0';
                }
            }
        }
    }

    for (i = 0; i < count; i++)
        display(filenames[i]);

    if(flag_param & PARAM_R) {  
        rewinddir(dir);

        for(i = 0; i < count-1; i++) {
            for(j = 0; j < count-1-i; j++) {
                if(strcmp(filenames[j],filenames[j+1]) > 0) {
                    strcpy(temp,filenames[j+1]);
                    temp[strlen(filenames[j+1])] = '\0';
                    strcpy(filenames[j+1],filenames[j]);
                    filenames[j+1][strlen(filenames[j])] = '\0';
                    strcpy(filenames[j],temp);
                    filenames[j][strlen(temp)] = '\0';
                }
            }
        }

        while( (ptr=readdir(dir)) != NULL)
        {
            char path_R[260];
            strncpy(path_R,path,sizeof(path));
            path_R[strlen(path_R)+1]='\0';
            strcat(path_R,ptr->d_name);
        //    printf("%s ",ptr->d_name);       重复打印一遍目录里的全部文件 
        //    printf("%s ",path_R);            重复打印一遍目录里的全部文件的路径
            int q = strlen(path_R);

            path_R[q]='\0';
            struct stat buf_R;
            lstat(path_R,&buf_R);

            if(ptr->d_name[0]!=46 && ptr->d_name[1]!=46 && S_ISDIR(buf_R.st_mode)) {
                printf("\n");
                char path_R[260];
                strncpy(path_R,path,sizeof(path));

                path_R[strlen(path_R)+1]='\0';
                strcat(path_R,ptr->d_name);
                int x = strlen(path_R);

                path_R[x]='/';
                path_R[x+1]='\0';

                printf("%s\n",path_R);
                display_dir(path_R);
            }
        }
    }
    
    closedir(dir);

    //如果命令行中没有-l选项，打印一个换行符
    if ( (flag_param & PARAM_L) == 0 )
        printf("\n");
}

void anal_param(int argc,char* argv[],char* path)
{
    int i, j, k, num;
    char param[32];   //保存命令行参数，目标文件名和目录名不在此列
    int flag_param = PARAM_NONE;   //参数种类，即是否有-l和-a选项
    struct stat buf;

    //命令行参数的解析，分析-l，-a，-al......选项
    j = 0,
    num = 0;
    for (i=1; i<argc; i++) {
        if (argv[i][0] == '-') {
            for (k=1; k < strlen(argv[i]); k++,j++) {
                param[j] = argv[i][k];
            }
        num++;
        }
    }

    //只支持参数a,l,r,R,i，如果含有其他选项就报错
    for (i=0; i<j; i++) {
        if (param[i] == 'a') {
            flag_param |=PARAM_A;
            continue;
        } else if (param[i] == 'l') {
            flag_param |=PARAM_L;
            continue;
        } else if (param[i] == 'R') {
            flag_param |=PARAM_R;
            continue;
        }else if (param[i] == 's') {
            flag_param |=PARAM_S;
            continue;
        } else if (param[i] == 't') {
            flag_param |=PARAM_T;
            continue;
        }else if (param[i] == 'r') {
            flag_param |=PARAM_r;
            continue;
        } else if (param[i] == 'i') {
            flag_param |=PARAM_I;
            continue;
        } else {
            printf("my_ls: invalid option -%c\n",param[i]);
            exit(1);
        }
    }
    param[j] = '\0';

    //如果没有输入文件名或目录，就显示当前目录
    if ((num + 1) == argc) {
        strcpy(path, "./");
        path[2] = '\0';
    }

    i = 1;
    do {
        //如果不是目标文件名或目录，解析下一个命令行参数
        if (argv[i][0] == '-') {
            i++;
            continue;
        } else {
            strcpy(path, argv[i]);

            //如果目标文件或目录不存在，报错并退出程序
            if ( stat(path, &buf) == -1 )
                my_err("stat",__LINE__);
            
            if ( S_ISDIR(buf.st_mode) ) {    //argv[i]是一个目录
                //如果目录的最后一个字符不是'/',就加上'/'
                if( path[ strlen(argv[i])-1 ] !='/' ) {
                    path[ strlen(argv[i]) ] = '/';
                    path[ strlen(argv[i])+1 ] = '\0';
                }
                else
                    path[ strlen(argv[i]) ] = '\0';
                i++;
            }
            i++;
        }
    } while (i<argc);
}
int main(int argc, char ** argv)
{
    int i, j, k, num;
    char path[260];
    char param[32];   //保存命令行参数，目标文件名和目录名不在此列
    int flag_param = PARAM_NONE;   //参数种类，即是否有-l和-a选项
    struct stat buf;

    anal_param(argc,argv,path);
    //如果没有输入文件名或目录，就显示当前目录
    if ((num + 1) == argc) {
        display_dir(path);
        return 0;
    }

    i = 1;
    do{
        if ( S_ISDIR(buf.st_mode) ) {
            display_dir(path);
            i++;
        }
        else {      //argv[i]是一个文件
            display(path);
        }
        i++;
    } while (i<argc);

    return 0;
}