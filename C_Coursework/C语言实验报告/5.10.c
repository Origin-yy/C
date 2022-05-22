#include <stdio.h>
#include <math.h>

int is_prime(int t)
{
    for (int i = 2; i <= sqrt(1.0 * t); i++)
        if (t % i == 0)
            return 0;
    return 1;
}

int main()
{
    int m;
    scanf("%d", &m);
    for(int i=2; i<=m;i++)
    {
        int n=i;
        while(m%n == 0)
        {
            if(is_prime(n))
                printf("%d ",n);
            m /= n;
        }
    }
            
    return 0;
}