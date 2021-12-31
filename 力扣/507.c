#include<stdio.h>
int main(void)
{
    int num = 0;
    int a[100000] = {0};
    int sum = 0;

    scanf("%d",&num);

    for(int i = 1;i < num;i++)
    {
        if(num/i*i == num)
        {
            sum += i;
        }
    }
    if(num == sum)
    {
        printf("true");
    }
    else
        printf("false");
    
    return 0;
}