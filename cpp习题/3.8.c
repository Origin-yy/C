#include<stdio.h>
int main (void)
{
    float n;
    printf("请输入杯数：");
    scanf("%f",&n);
    printf("即%f品脱\n",n/2);
    printf("即%f盎司\n",n*8);
    printf("即%f汤勺\n",n*16);
    printf("即%f茶勺\n",n*48);
    return 0;
}