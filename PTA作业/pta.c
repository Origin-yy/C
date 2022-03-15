#include<stdio.h>

int main (void)
{
	int x,a,b,c;
	scanf("%d",&x);
	a = x/100;
	c = x%10;
	b = x/10%10;
 	printf("%d%d%d",c,b,a);
	return 0;
}