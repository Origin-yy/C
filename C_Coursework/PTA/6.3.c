#include<stdio.h>
#include<string.h>
#include<malloc.h>
int main(void)
{
    //char *a = (char*)malloc(sizeof(char)*40);
    //char *b = (char*)malloc(sizeof(char)*40);
    char a[6];
    char b[9];
    scanf("%s",a);
    scanf("%s",b);

    printf("%s\n",a);
    printf("%s\n",b);

    return 0;
}