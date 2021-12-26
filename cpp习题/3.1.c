#include <stdio.h>

int main(void)
{
    int int_max = 2147483647;
    printf("%d %d\n",int_max,int_max+1);

    float float_max = 3.40e38;
     printf("%f %f\n",float_max,float_max+1);

    float float_min = 3.40e-38;
    printf("%f %f",float_min,float_min-1);

    return 0;
}