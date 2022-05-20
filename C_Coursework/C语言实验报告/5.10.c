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
    int m, n = 0;
    scanf("%d", &m);
    int a[m];
    for (int i = 2; i < m; i++)
        if (m % i == 0)
            a[n++] = i;
            
    for (int i = 0; i < n; i++)
        if (is_prime(a[i]) || a[i] == 2)
            printf("%d\t", a[i]);
    return 0;
}