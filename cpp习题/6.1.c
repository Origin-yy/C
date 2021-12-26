#include<stdio.h>
int main(void)
{
    char a[26];
    int i;

    for(i = 0;i < 26;i++)
    {
        a[i] = 'a' + i;
        printf("%c ",a[i]);
    }
    return 0;
}