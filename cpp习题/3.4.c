#include<stdio.h>
int main (void)
{
    float n;
    
    printf("Enter a floating-point vaues:\n",n);
    scanf("%f",&n);
    printf("fixed-point notation:%f\n",n);
    printf("exoinential notation:%e\n",n);
    printf("p notation:%#a\n",n);
    
    return 0;
}