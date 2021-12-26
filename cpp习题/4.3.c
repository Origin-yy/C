#include<stdio.h>
int main(void)
{
    float a;

    printf("请输入一个浮点数：\n");
    scanf("%f",&a);
    printf("The input is %f or%e.\n",a,a);
    printf("The input is +%f or %E.\n",a,a);

    return 0;
}