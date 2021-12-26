#include <stdio.h>
int main(void)
{
    int k;
    printf("请输入水的夸脱数：");
    scanf("%d",&k);
    printf("水分子数为%e.\n",k*950/3.0e-23);
    return 0;
}