#include<stdio.h>
#define BASIC 10.00
#define Over 1.5
#define FIRST_RATE 0.15
#define NEXT_RATE 0.20
#define FIRST_SUM 300 * 0.85
#define NEXT_SUM 150 * 0.8

int main(void)
{
    int times;

    while (scanf("%d",&times) == 1)
    {
        if(times < 300/10)
            printf("%lf",(double)10*times*(1 - 0.15));
        else if (times < 400/10)
            printf("%lf",FIRST_SUM + (double)(times*10 - 300)*0.8);
        else
            printf("%lf",FIRST_SUM + NEXT_SUM + (double)(times*10 - 40) *1.5 * 10 * 0.75);        
    }

    return 0;
}