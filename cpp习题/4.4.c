#include<stdio.h>
int main (void)
{
    float cm;
    
    printf("请输入您的身高（单位：厘米）：\n");
    scanf("%f",&cm);
    printf("Dabney, you are %f feet tall.\n",cm/100);
}