#include<stdio.h>
int main(void)
{
    int a[8];
    int i;

    printf("请输入八个整数：");

    for (i = 0;i < 8; i++)
    {
        scanf("%d",&a[i]);
    }
    for (i = 7; i > -1; i--)
    {
        printf("%d ",a[i]);
    }
    return 0;
}