#include<stdio.h>
int main(void)
{
    char ch;
    int n = 0;
    int f = 0;

    while((ch = getchar()) != '#')
    {
        switch(ch)
        {
            case 'e' :
                f = 1;
                break;
            case 'i' :
                if(f)
                    {
                        n++;
                        f = 0;
                    }
                break;
            default :
                f = 0;
        }
    }
    printf("\n%d\n",n);
    return 0;
}