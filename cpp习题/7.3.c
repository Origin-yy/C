#include<stdio.h>
int main(void)
{
    int i = 0;
    int j = 0;
    int sum1 = 0;
    int sum2 = 0;
    int x;

    while (scanf("%d",&x) == 1 && x)
    {
        if (x % 2 == 0)
        {
            i++;
            sum1 += x;
        }
        else
        {
            j++;
            sum2 += x;
        }
    }
        printf("偶数个数为 %d，平均值为 %lf。\n奇数个数为 %d，平均值为%lf。",
                i,(double)sum2/i,j,(double)sum2/j);
        return 0;

}