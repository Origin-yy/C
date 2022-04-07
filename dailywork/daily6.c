//sinx按泰勒公式展开为：sinx=x-x^3/3!+x^5/5!-x^7/7!+x^9/9!-……+(-1)^(n-1)*(x^(2n-1)/(2n-1)!)
//最后一项：(-1)^(n-1)*(x^(2n-1)/(2n-1)!)
#include<stdio.h>

int main(void)
{
    //t为每一项，up为分子，down为分母
    double x = 0,t = 1,sum = 0;
    int n = 1;
    scanf("%lf",&x);
    while(t>=0.00001)
    {
        double up = 1;
        for (int i = 1;i<=2*n-1;i++)
        {
            up *= x;
        }

        double down = 1;
        for(int i = 1;i<=2*n-1;i++)
        {
            down *= i;
        }

        t= up/down;
        
        if(n%2 == 0)
            sum -= t;
        else
            sum += t;
        n++;
    }
    printf("%lf",sum);

    return 0;
} 
