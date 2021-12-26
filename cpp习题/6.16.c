#include<stdio.h>
int main (void)
{
    int i = 0;
    double sum1 = 100;
    double sum2 = 100;
    do
    {
        i++;
        sum1 += 10;
        sum2 *= 1.05;
    } while (sum1 > sum2);
    printf("%d年后，Deirdre的投资额会超过Daphne，此时Deirdre的投资额为%lf美元,Daphne的投资额为%lf美元.\n",i,sum2,sum1);

}