#include <stdio.h>
#include <math.h>

int is_prime(int t)
{
    for (int i = 2; i <= sqrt(1.0 * t); i++)
    {
        if (t % i == 0)
            return 0;
    }
    return 1;
}
int main(void)
{
    int a[2000] = {2, 0};
    int b[2000] = {0};
    int n = 1, sum = 0;
    for (int i = 3; i < 1994; i++)
        if (is_prime(i))
            a[n++] = i;
    for (int i = 0; i < n - 1; i++)
        b[i] = a[i + 1] - a[i];
    for (int i = 0; i < n; i++)
        sum += b[i];
    //以下代码查看第二行所有数以及他们的和
    //for (int i = 0; i < n-1; i++)
    //    printf("%d\t",b[i]);
    //printf("\n%d\n",sum);
    if (sum < 1898)
        printf("没有这样的若干连续正整数,他们的和是1898\n");
    else
    {
        int cha = sum - 1898;
        int he1 = 0, he2 = 0, mark = 0;
        for (int i = 0; i < n - 1; i++)
        {
            he1 += b[i];
            he2 += b[n - 2 - i];
            //printf("%d %d\n",he2,b[n-2-i]);
            //printf("%d %d\n",he1,b[i]);
            if (he1 == cha)
                mark++;
            if (he2 == cha)
                mark++;
            if (he1 > cha && he2 > cha)
                break;
        }
        printf("%d %d",cha,mark);
        if (mark != 0)
            printf("有%d种这样的若干连续正整数,他们的和是1898\n", mark);
        else
            printf("没有这样的若干连续正整数,他们的和是1898\n");
    }
    return 0;
}