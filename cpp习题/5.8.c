
#include<stdio.h>
int main (void)
{
    int second_operand = 0;
    int first_operand = 0;

    printf("This program computers moduli.\n");
    printf("Enter an integer to servw as the second operand:\n");
    scanf("%d",&second_operand);
    printf("Now enter the first operand:\n");
    scanf("%d",&first_operand);

    printf("%d %% %d is %d\n",first_operand,second_operand,first_operand%second_operand);

    printf("Enter next number for first operand (<=0 to quit):\n");
    scanf("%d",&first_operand);

    while (first_operand > 0)
    {
        printf("%d %% %d is %d\n",first_operand<second_operand,first_operand%second_operand);
        printf("Enter next number for first operand (<= )to quit):\n");
        scanf("%d",&first_operand);
    }
    
    printf("Done\n");
}