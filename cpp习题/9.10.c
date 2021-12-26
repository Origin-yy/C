#include<stdio.h>
void to_base_n( int base, int n )
{
	int x;

	x = base % n;
	if( base>=n )
	{
		to_base_n(base / n, n);
	}

	printf("%d",x);
}
int main()
{
	int base,n;
	scanf("%d %d",&base,&n);
	printf("When we convert %d to %d,we get ",base,n);
	to_base_n(base,n);
	
	return 0;
}
