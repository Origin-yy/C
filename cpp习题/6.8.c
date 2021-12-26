#include<stdio.h>
int main(void)
{
    double a,b;
    printf("请输入两个浮点数：\n");

    while (scanf("%lf %lf",&a,&b) == 2)
    {
        printf("%lf\n",(a - b)/a * b);
        printf("请继续输入：（输入q停止）");
    }
}