#include<stdio.h>
int main(void)
{
    int i = -1;
    char a[255];

    do
    {
        i++;
        scanf("%c",&a[i]);
    } while (a[i] != '\n');

    for( ;i >=0;i--)
        printf("%c",a[i]);
    printf("\n");
    return 0;
}