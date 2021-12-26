#include<stdio.h>
int main (void)
{
    char m[10],n[10];

    printf("请输入名字和姓名（以空格隔开):\n");
    scanf("%s%s",m,n);
    printf("您的名字和姓名为：\n%s,%s\n",m,n);

    return 0;

}