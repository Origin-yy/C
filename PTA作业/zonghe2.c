#include<stdio.h>
#include<string.h>
#include<math.h>
int main()
{
    char c[10];
    printf("请输入一个运算符：");
    scanf("%s",c);
    if(c[0] == '+' || c[0] == '-' || c[0] =='*' || c[0]== '%'|| c[0] =='/')
    {
        printf("请输入两个操作数：");
        float a,b;
        scanf("%f%f",&a,&b);
        switch(c[0])
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
    }
    else
    {
        printf("请输入一个操作数：");
        float d;
        scanf("%f",&d);
        if(strcmp("sin",c)==0)
            printf("sin%f=%.2f",d,sin(d));
        else if(strcmp("cos",c)==0)
            printf("cos%f=%.2f",d,cos(d));
        else if(strcmp("tan",c)==0)
            printf("tan%f=%.2f",d,tan(d));
        else if(strcmp("exp",c)==0)
            printf("exp(%f)=%.2f",d,exp(d));
        else if(strcmp("sqrt",c)==0)
            printf("sqrt%f=%.2f",d,sqrt(d));
    }
    return 0;
}
