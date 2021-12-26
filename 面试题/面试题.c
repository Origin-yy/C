#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#define N 44
char *convert(const char *s);
int main()
{
    char *str="XiyouLinux Group 2022";
    char *temp=convert(str);
    puts(temp);
    return 0;
}
char *convert(const char *s)
{
    int len=strlen(s);
    char *k=(char*)malloc(N);//在函数中分配一段空间并且让指针k指向这段字符串的位置
    char *t=s;//指针t用来保存原字符串s的位置
    memset(k,0,N);//将新分配的内存空间中的数全部置为0
    char str[N];//用一个数组来存放转换后的字符串
    for(int i=0;*s!='\0';*s++,i++)
    {
        if(*s>='a'&&*s<='z')
            str[i]=toupper(*s);
        else if(*s>='A'&&*s<='Z')
            str[i]=tolower(*s);
        else 
            str[i]=*s;
    }
    strcpy(k,str);//将转换后的字符串存放进申请的新内存空间
    t=k;//使存放原s字符串的位置的指针改指向新的位置(新分配的内存空间)
    return t;
}