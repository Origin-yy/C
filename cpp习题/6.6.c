#include<stdio.h>
int main(void)
{
    int i,x;

    printf("请输入一个整数（输入q停止），程序会打印这个数和他的立方，平方：\n");

    for(i = 1;scanf("%d",&x) == 1;i++)
    {
        printf("%d\t %d\t %d\n",x,x*x,x*x*x);
        printf("请继续输入：\n");
    }

    return 0;
}