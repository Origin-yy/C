#include<stdio.h>

int main()
{
    float a;
    scanf("%f",&a);
    if(a<=50)
        printf("%.2f公斤，%.2f元",a,0.15*a);
    else
        printf("%.2f公斤，%.2f元",a,50*0.15+(a-50)*0.25);
    return 0;
}

