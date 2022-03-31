#include <stdio.h>
int main(void)
{
    double n = 1,s = 0;
    while(s <= 15)
    {
        s += 1/n;
        n++;
    }
    printf("N = %d,S = %f",(int)n,s);
    return 0;
}
