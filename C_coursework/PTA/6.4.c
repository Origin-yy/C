#include<stdio.h>
int main(void)
{
    int a,b,t;
    int *pa = &a;
    int *pb = &b;
    scanf("%d %d",&a,&b);
    printf("a=%d,b=%d\n",a,b);
    t = *pa;
    *pa = *pb;
    *pb = t;
    printf("a=%d,b=%d",a,b);
    
    return 0;
}