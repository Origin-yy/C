#include<stdio.h>
int main(void)
{
    double h = 0.2;
    int cnt = 0;
    while (h <= 8848000)
    {
        h = h*2;
        cnt++;
    }
    printf("%d次",cnt);

    return 0;
}