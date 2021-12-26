#include<stdio.h>
int main()
{
	double bonus = 100.00;
	int years = 0;
	
	do
	{
		years++;
		bonus += bonus*0.08;
		bonus -= 10.0;
	}while(bonus > 0);
	printf("years: %d\n",years);
	
	return 0;	
}
