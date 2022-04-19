#include<stdio.h>
int mian(void)
{
    int i;
    for(i = 0; i<10000; i++)
    {
        if((i%100+i/100)*(i%100+i/100) == i)
            printf("%d\n",i);
    }
    return 0;
}