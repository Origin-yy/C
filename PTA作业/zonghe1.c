#include<stdio.h>
int main()
{
    float a,b;
    char c;
    scanf("%f%c%f",&a,&c,&b);
    switch(c)
    {
        case '+':
            printf("%f+%f=%.2f",a,b,a+b);
        break;
        case '-':
            printf("%f-%f=%.2f",a,b,a-b);
        break;
        case '*':
            printf("%f*%f=%.2f",a,b,a*b);
        break;
        case '/':
            if(b==0)
            {
                printf("0不能做除数");
                break;
            }
            else
            {
                printf("%f/%f=%.2f",a,b,a/b);
                break;
            }
        case'%':
            printf("%d%%%d=%d",(int)a,(int)b,(int)a%(int)b);
            break;
    }
    return 0;
}
