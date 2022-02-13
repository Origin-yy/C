#include<stdio.h>
#include<algorithm>
#include<iostream>
struct node
{
    int n,v;
    double r;
}a[100];

int cmp( struct node a,struct node b)
{
    return a.r >b.r;
}

int main(void)
{
    int k = 0;
    scanf("%d",&k);
    for(int i = 0;i < k;k++)
    {
        int w,s;
        scanf("%d %d",&w,&s);
        for(int i = 1;i <= s;i++)
        {
            scanf("%d %d",&a[i].n,&a[i].v);
            a[i].r = (double)a[i].n/a[i].v;
        }
        sort(a.a+s,cmp);
        double ans = 0;
        for(int i = 1;i<= s;i++)
        {
            if(w >= a[i].n)
            {
                ans += a[i].v;
                w -= a[i].n;
            }
            else
            {
                ans += (a[i].v/a[i].n*w);
                break;
            }
        }
        printf("%.2lf\n",ans);
    }
    return 0;
}