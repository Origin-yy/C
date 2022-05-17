#include<stdio.h>
int main (void)
{
    for (int i=1;i<=1000;i++)
    {
        int cnt = 0;
        int sum = 0;
        int a[1000] = {0};

        for(int j=1;j<=i;j++)
        {
            if(i%j == 0)
            {
                a[cnt++] = j;
            }
        }

        for(int j=0;j<cnt-1;j++)
        {
            sum += a[j];
        }

        if(sum == i)
        {
            printf("%d its factors are ",i);
            for(int j=0;j<cnt-1;j++)
            {
                printf("%d",a[j]);
                if(j < cnt-2)
                    printf(", ");
                else
                    printf("\n");
            }

        }
    }
    return 0;
}