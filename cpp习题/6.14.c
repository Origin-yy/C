#include<stdio.h>
int main(void)
{
    int i;
    double a[8],b[8];

    printf("请输入八个浮点数：\n");
    for(i = 0;i < 8;i ++)
        scanf("%lf",&a[i]);

    b[0] = a[0];
    for(i = 1;i < 8;i++)
        b[i] = b[i-1] + a[i];  

    for(i = 0;i < 8;i++)
        printf("%5.2lf",a[i]);
    printf("\n");

    for(i = 0;i < 8;i++)    
        printf("%5.2lf",b[i]);
    printf("\n");

    return 0;
}