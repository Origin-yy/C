#include<stdio.h>
void cubic(void);

int main(void)
{
    printf("Enter a number in double type.\n");
    cubic();

    return 0;
}

void cubic(void)
{
    double number;
    scanf("%lf",&number);
    printf("The cube of this number is %f",number*number*number);
}
