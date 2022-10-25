#include<stdio.h>

int main(void)
{
    char a = 0;
    char b = 0;
    scanf("%c", &a);
    scanf(" %c", &b);

    printf("%c\n", a);
    printf("%c\n", b);

    return 0;
}