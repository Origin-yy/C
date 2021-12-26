#include<stdio.h>
void Fibonacci(int n)
{
	int i;
	int x,y,z;
	for( i=1; i<=n; i++ )
	{
		if( i==1 )
		{
			x = 1;
			printf("%d ",x);
		}
		else if( i==2 )
		{
			y = 1;
			printf("%d ",y);
		}
		else
		{
			z = x+y;//当前的值
			x = y;//下一次求和中较小的值
			y = z;//下一次求和中较大的值
			printf("%d ",z);
		}
	}
	putchar('\n');
}

int main()
{
	int n;
	scanf("%d",&n);
	Fibonacci(n);
	
	return 0;
}
