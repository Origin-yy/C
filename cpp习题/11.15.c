#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define LEN 10

char *s_gets(char *st, int n);
int myatoi(char *str);

int main(int argc, char *argv[])
{
    char input[LEN];

    printf("Please enter a string (EOF to quit):\n");
    while (s_gets(input, LEN) != NULL)
    {
        printf("String %s convert number %d\n", input, myatoi(input));
        printf("You can enter a string again (EOF to quit):\n");
    }
    printf("Done.\n");

    return 0;
}

char *s_gets(char *st, int n)
{
    char *ret_val;
    char *find;

    ret_val = fgets(st, n, stdin);
    if (ret_val)
    {
        find = strchr(st, '\n');
        if (find)
        {
            *find = '\0';
        }
        else
        {
            while (getchar() != '\n')
                continue;
        }
    }
    return ret_val;
}

int myatoi(char *str)
{
    int i;
    int n = 0;

    for (i = 0; i < strlen(str); i++)
    {
        if (!isdigit(str[i]))
        {
            return 0;
        }
        else
        {
            n = n * 10 + (str[i] - '0');
        }
    }
    return n;
}
