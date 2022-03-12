#include<stdio.h>
#include<sys/types.h>//opendir
#include<dirent.h>//opendir,readdir

int main (int argc,char* argv[])
{
    if(argc == 1)
        do_ls(".");
    else
        do_ls(*argv[1]);
    return 0;
}

void do_ls(char dirname[])
{
    DIR *dir = opendir(dirname);
    struct dirent *direntp;
    if(dir == NULL)
        printf("my_ls：无法访问‘%s’：没有那个文件或目录\n",dirname);
    else
    {
        while((direntp = readdir(dir) != NULL))
            printf("%s\n",direntp->d_name);
        clsodir(dir);
    }

}