#include<stdio.h>
int main()
{
    int i = 0;
    int j =0;
    i = 3;
    j = (++i) + (++i) * (++i);
    printf("i:%d,j:%d\n",i,j);
}