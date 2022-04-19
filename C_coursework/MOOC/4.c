#include<stdio.h>
int main(void)
{
    for(int i=1000; i<10000;i++)
    {
        if((i/100)%11 == 0  && (i%100)%11 == 0)
        {
            for(int j=0; j<100;j++)
                if(j*j == i)
                    printf("The number is %d.\n",i);
        }
    }
    return 0;
}