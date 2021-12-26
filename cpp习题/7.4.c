#include<stdio.h>
#include<stdlib.h>
int main(void)
{
	char ch;
	int n = 0;
	
	while ((ch = getchar()) != '#')
	{
		if (ch == '.')
		{
			putchar('!');
			n++;
		}
		else if (ch == '!')
		{
			putchar('!');
			putchar('!');
			n++;
		}
		else
			putchar(ch);
	}
	printf("\n%d\n",n);

	return 0;	
 }
