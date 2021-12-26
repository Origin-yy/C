#include<stdio.h>
void copy(double target[],double source[],int len)
{
    for(int i = 0;i < len;i++)
        target[i] = source[i];
}

int main(void)
{
    double arr2[3][3];
    double arr1[3][3] = {
                        {1.1,1.2,1.3},
                        {2.1,2.2,2.3},
                        {3.1,3.2,3.3},
                        };
    for(int i = 0;i < 3;i++)
    {
        copy(arr2[i],arr1[i],3);
    }
    for(int i = 0 ;i < 3;i++)
    {
        for(int j = 0;j < 3;j++)
            printf("%.1lf\t",arr2[i][j]);
        printf("\n");
    }
}