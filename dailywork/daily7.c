#include<stdio.h>
//注：当输入为偶数时，为保证形状，宽度为d+1
int main(void)
{
    int d;
    scanf("%d",&d);

    for(int i=0; i<d/2; i++)
    {
        for(int j=0; j<d/2-i; j++)
            printf(" ");

        printf("*");

        if(i > 0)
            for(int j = 0; j<2*i-1; j++)
                printf("+");
        if(i > 0)
            printf("*\n");
        else
            printf("\n");
    }

    printf("*");
    for(int i = 0; i<d-2; i++)
        printf("+");
    if(d%2 == 0)
        printf("+");
    printf("*\n");

    for(int i=d/2-1; i>=0; i--)
    {
        for(int j=0; j<d/2-i; j++)
            printf(" ");

        printf("*");

        if(i > 0)
            for(int j = 0; j<2*i-1; j++)
                printf("+");
        if(i > 0)
            printf("*\n");
        else
            printf("\n");
    }

    return 0;
}
    