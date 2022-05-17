#include<stdio.h>
#include<stdlib.h>

int cmp(const void*x,const void*y)
{
    return *(int*)x - *(int*)y;
}

int main (void)
{
    int a[5][4] = {0};
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<5; j++)
        {
            scanf("%d",&a[j][i]);
            if(j != 4)
                scanf(" ");
        }
    }
    for(int i=0; i<5; i++)
        qsort(a[i],4,sizeof(int),cmp);
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<5; j++)
            printf("%4d",a[j][i]);
        printf("\n");
    }
    return 0;
}