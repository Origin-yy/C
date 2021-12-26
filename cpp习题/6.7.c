#include<stdio.h>
#include<string.h>
int main (void)
{
    char letters[20];
    int i;

    printf("Please enter a word(Ctrl+D is to quit):\n");
    while(scanf("%s",letters) == 1)
    {
        for (i =strlen(letters) - 1;i >= 0; i--)
        {
            printf("%c",letters[i]);
        }
        printf("\n");
    }
    return 0;
}