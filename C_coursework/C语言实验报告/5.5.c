/*
求两个正整数最大公约数和最小公倍数
用欧几里德算法(辗转相除法)求两个数的最大公约数
两个正整数的最小公倍数=两个数的乘积/两个数的最大公约数
*/
#include<stdio.h>

int hcf(int, int);
int lcd(int, int, int);

int main()
{
    int a, b, h, l;
    scanf("%d,%d", &a, &b);
    h = hcf(a,b);
    printf("H.C.F=%d\n", h);
    l = lcd(a, b, h);
    printf("L.C.D=%d\n", l);
    return 0;
}
int hcf(int u, int v)
{
    int t, r;
    if (v > u)
    {
        t = u;
        u = v;
        v = t;
    }
    while ((r = u % v) != 0)
    {
        u = v;
        v = r;
    }
    return (v);
}
int lcd(int u, int v, int h)
{
    return (u * v / h);
}