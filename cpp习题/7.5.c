#include<stdio.h>
int main(void)
{
	char ch;
	int n = 0;
	
	while ((ch = getchar()) != '#')
	{
		switch (ch)
		{	
			case '.': 
				putchar('!');
				n++;
				break;
			
			case '!': 
				putchar('!');putchar('!');
				n++;
				break;
			default :
				putchar(ch);
				break;
		}
	}
	printf("\n%d\n",n);

	return 0;	
}
