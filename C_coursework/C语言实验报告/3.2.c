#include <stdio.h>
int main(int argc, char** argv)
{
    double s;
    double t=1;
    int n = 1;
    while (1/t > 0.000001)
    {
        t=1;
        for(int i=1;i<=n;i++)
        {
            t *= i;
        }
        if(n%2 == 1)
            s += 1/t;
        else
            s -= 1/t;
        n++;
    }
    printf("S = %lf.\n",s);
    return 0;
}
