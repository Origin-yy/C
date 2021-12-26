#include<stdio.h>
int main(void)
{
    int i,j;
    char a = 'F';

    for(i = 1; i <= 6; i++)
    {
        for(j = 1; j <= i; j++)
        {
            printf("%c",a - j + 1);
        }
        printf("\n");
    }
}