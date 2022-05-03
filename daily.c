int mymod(int a, int b)
{
    int s, ys;
    s = a / b;
    ys = a-s*b;
    return ys;
}
#include <stdio.h>
int main(void)
{
    int x, y, myys;
    scanf("%d %d",&x,&y);
    myys =mymod(x,y);
    printf("%d",myys);
    return 0;
}