#include <stdio.h>
#include <math.h>
int main(void)
{
	int number[8];
	int i;
	
	for (i = 0;i < 8;i++)
	{
		number[i] = pow(2,i+1);
	}
	i = 0;
	do
	{
		printf("%d ",number[i]);
		i++;
	}while(i < 8);
	
	return 0;
}