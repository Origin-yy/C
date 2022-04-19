#include <stdio.h>
int main(void)
{
    int n, sum = 0, temp = 0;
    scanf("%d", &n);
    if (n < 1)
        printf("Error!");
    else
    {
        for (int i = 1; i <= n; i++)
        {
            temp = 0;
            for (int j = 1; j <= i; j++)
                temp += j;
            sum += temp;
        }
        printf("%d", sum);
    }
    return 0;
}