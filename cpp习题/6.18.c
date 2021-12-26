#include<stdio.h>
int main(void)
{
	int friends = 5;
	int weeks = 0;
	do
	{
		weeks++;
		friends = (friends - weeks) * 2;
	}while(friends < 150);
	printf("Weeks: %d",weeks);
	
	return 0;
}
