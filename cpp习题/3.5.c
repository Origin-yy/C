#include <stdio.h>
int main (void)
{
    int years;
    printf("请输入你的年龄：");
    scanf("%d",&years);
    printf("你的年龄转换成秒数是：%e\n",years*3.156e7);
    return 0;
}