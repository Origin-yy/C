#include<stdio.h>
#include<string.h>
#include<malloc.h>
int main(void)
{
    char *a = (char*)malloc(sizeof(char)*40);
    char *b = (char*)malloc(sizeof(char)*40);
    int num_a,num_b;
    scanf("%s",a);
    scanf("%s",b);
    num_a = strlen(a);
    num_b = strlen(b);
    for(int i=0; i<num_b; i++)
        *(a+num_a+i) = *(b+i);
    printf("%s",a);
    free(a);
    free(b);
    return 0;
}