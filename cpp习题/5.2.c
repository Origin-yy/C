#include <stdio.h>
int main (void)
{
    int i,n;

    printf("请输入一个整数：\n");
    scanf("%d",&n);

    for(i = n;i < n+16;i++)
    printf("%d\n",i);

    return 0;
}