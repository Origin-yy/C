#include <stdio.h>
int main (void)
{
    double h,sum,inches;
    int feet;

    printf("Enter a height in centimeters:");
    scanf("%lf",&h);

    while (h > 0)
    {
        sum = h/2.54;
        feet = (int)(sum/12);
        inches = sum - (double)feet*12;
         
        printf("%.1lf = %d feet,%.1lf inches.\n",h,feet,inches);

        printf("Enter a height in centimeters(0 is to quit):");
        scanf("%lf",&h);
    }
    printf("bye.\n");

    return 0;
}