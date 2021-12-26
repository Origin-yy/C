#include <stdio.h>
#include <math.h>
int main(void)
{
    int limit;
    int i;
    float sum1, sum2;

    printf("Please inter the limit.\n");
    while (scanf("%d", &limit) == 1 && limit > 0)
    {
        for (i = 0; i < limit; i++)
        {
            sum1 += 1.0 / (1.0 + i);
            sum2 += 1.0 / (1.0 + i) * pow(-1, i);
        }
        printf("The firse result is %f\n", sum1);
        printf("The second result is %f\n", sum2);
    }
    return 0;
}