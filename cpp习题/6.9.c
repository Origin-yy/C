#include<stdio.h>
void result(double n1,double n2);
int main (void)
{
    double n1,n2;

    printf("Please enter two float number.\n");
    while (scanf("%lf %lf",&n1,&n2) == 2)
    {
        result(n1,n2);
    }

    return 0;
}

void result(double n1,double n2)
{
    printf("The difference between these two numbers is divided by thr two-dight product is %lf\n",
    (n1 - n2)/(n1*n2));
    printf("Enter again.\n");
}
