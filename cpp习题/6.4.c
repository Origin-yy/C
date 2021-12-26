#include<stdio.h>
int main(void)
{
    int i,j;
    int n = 0;
    char a = 'A';

    for(i = 1; i <= 6; i++)
    {
        for(j = 1; j <= i; j++)
        {
            printf("%c",a + n);
            n ++;
        }
        printf("\n");
    }
}