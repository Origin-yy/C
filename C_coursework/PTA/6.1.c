#include<stdio.h>
int main (void)
{
    int n = 0,a[200] = {0},m = 0;
    int *p = NULL;
    scanf("%d %d",&n,&m);
    for(int i=0; i<n; i++)
    {
        scanf("%d",&a[i]);
        if(i != n-1)
            scanf(" ");
    }
    for(int i=0; i<m; i++)
        a[n+i] = a [i];
    p = a+m;
    for(int i=0 ;i<n; i++)
        a[i] = *p++;
    for(int i=0; i<n; i++)
    {
        printf("%d",a[i]);
        if(i != n-1)
            printf(" ");
    }
    return 0;
}