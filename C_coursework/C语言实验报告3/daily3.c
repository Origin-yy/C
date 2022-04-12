#include<stdio.h>
int main(void)
{
    int a=0,b=0;

    for (int i=101;i+2<200;i++)
    {
        a = i;
        b = i+2;
        for(int j=2;j<=i/2;j++)
        {
            if( a%j == 0)
            {
                a = 0;
                break;
            }
        }
        if(a != 0)
            for(int j=1;j<=j/2;j++) 
            {
                if( b%j == 0)
                {
                    b = 0;
                    break;
                }
            }
        if(a != 0 && b !=0 )
        {
            printf("%d,%d\n",a,b);
        }
    }
    return 0;
}