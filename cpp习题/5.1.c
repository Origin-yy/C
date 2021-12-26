#include <stdio.h>
#define MIN 60

int main(void)
{
    int t,hour,min;

    printf("Please enter minutes(0 is to quit).\n");
    scanf("%d",&t);
    while (t>0)
    {
        hour = t / MIN;
        min = t % MIN;
        if(hour > 1)
            printf("%d minutes is %d hours and %d minutes.\n",t,hour,min);
        else
            printf("%d minutes is %d hour and %d minutes.\n",t,hour,min);

        scanf("%d",&t);
    }
    return 0;
}