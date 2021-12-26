#include<stdio.h>

int main(void)
{
    int max = 100;
    int min = 0;
    int n = 50;
    int x = 0;
    int answer;

    printf("请输入一个1~100之间的数：\n");
    scanf("%d",&x);
    while(n != x)
    {
        printf("这个数是%d吗？（1表示猜大了，2表示猜小了）.\n",n);
        scanf("%d",&answer);
        if(answer == 1)
        {
            max = n;
            min = min;
            n = (min + max)/2;
        }
        else if(answer == 2)
        {
            min = n;
            max = max;
            n = (min + max)/2;
        }
        else{
            printf("输入有误，请重新输入。\n");
            while(get1char() != '\n')
                continue;
        }
    }
    printf("我就知道这个数是%d",n);

    return 0;
}