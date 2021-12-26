#include<stdio.h>                                
int main(void)
{
	int count, sum, n;
	sum = 0;
	count = 0;
	
	printf("How many days dou you want to work?\n");
	scanf("%d",&n);
	while(count++ < n)
		{
			sum = sum + count*count;
		}
	printf("sum = %d\n",sum);
	
	return 0;
}
