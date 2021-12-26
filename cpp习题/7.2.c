#include<stdio.h>
int main(void)
{
	int n = 1;
	char ch;
	
	while ((ch = getchar()) != '#')
	{
		putchar(ch);
		printf(" %d ",ch);
		if (n++ % 8 == 0)
		printf("\n");
	}
	
	return 0;
 }
