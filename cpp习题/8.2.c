#include<stdio.h>
int main(void)
{
	int i = 0;
	char ch;
	
	while ((ch = getchar()) != EOF)
	{	
			if (ch == '\n')
			{
				putchar('\\');
				putchar('n');
				printf(" %d\t",ch);
				i = 0;
			}
			else if (ch == '\t')
			{
				putchar('\\');
				putchar('t');
				printf(" %d\t",ch);
			}
			else if(ch < ' ')    
			{				   							
				putchar('^');
				putchar(ch + 64);
				printf("%d\t",ch);
			}
			else
				printf("%c %d\t",ch,ch);

		if (i++ == 9)
		{
			printf("\n");
			i = 0;
		}
	}
	
	return 0;
}
