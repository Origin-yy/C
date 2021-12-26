#include<stdio.h>
int main(void)
{
    int h,l1,l2,l3;
    char A = 'A';

    for(h = 1; h <= 5; h++)
    {
        for(l1 = 4; l1 >= h; l1--)
        {
            printf(" ");
        }
        for(l2 = 1; l2 <= h; l2++)
        {
            printf("%c",A - 1 + l2);
        }
        for(l3 = 2; l3 <= h; l3++)
        {
            printf("%c",A + h - l3);
        }
        printf("\n");
    }
    return 0;
}