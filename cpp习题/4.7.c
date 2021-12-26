#include<stdio.h>
#include<float.h>
int main(void)
{
    double n1 = 1.0/3.0;
    float n2 = 1.0/3.0;

    printf("*%.6lf*\n*%.12*\n*%.16lf*\n",n1,n1,n1);

    printf("*%.6f*\n*%.12f*\n*%.16f*\n",n2,n2,n2);

    printf("FLT_DIG = %d\n",FLT_DIG);

    printf("DBL_DIG = %d\n",DBL_DIG);

    return 0;
}