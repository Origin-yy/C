#include<stdio.h>
int main(void)
{
    int i,a,b;
    
    printf("Enter lower and upper integer limits:");
    scanf("%d %d",&a,&b);

    while (a < b)
    {
        int sum = 0;
        for(i = 0; a + i <= b; i++)
        {
            sum += (a + i)*(a + i);
        }
        printf("The sums of the squaares from %d to %d is %d\n",a*a,b*b,sum);

        printf("$nter next set of limits:");
        scanf("%d %d",&a,&b);
    }
    printf("Done\n");

    return 0;
}