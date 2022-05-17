#include<stdio.h>
int main(void)
{
    int a[100],n=0;
    int temp=0;
    printf("请输入一个整形数组，每个数字用‘,’隔开,回车表示结束\n");
    do
    {
        scanf("%d",&a[n++]);
    } while (getchar() != '\n');
    printf("%d\n",n);
    for (int i=0; i<n/2; i++)
    {
        temp = a[i];
        a[i] = a[n-1-i];
        a[n-1-i] = temp; 
    }
    for(int i=0; i<n; i++)
    {
        printf("%d",a[i]);
        if(i!=n-1)
            printf(",");
        else
            printf("\n");
    }
    return 0;
}