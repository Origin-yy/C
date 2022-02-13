#include<stdio.h>
#include<stdlib.h>
struct node
{
    int n,v;
    double r;
}a[100];

int cmp(const void *p1,const void *p2)
{
    struct node*pp1 = (struct node*)p1;
    struct node*pp2 = (struct node*)p2;
    return (pp1->r > pp2->r ? 1:-1);
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
        qsort(a+1,s,sizeof(struct node),cmp);

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
                ans += ((double)a[i].v/a[i].n)*w;
                break;
            }
        }
        printf("%.2lf\n",ans);
    }
    return 0;
}