#include<stdio.h>
#include<string.h>
#define num 100
int main()
{
	char b[num] = { '\0' };
	char a[num] = { '\0' };
	gets(a);
	int n = strlen(a);
	int count = 0;
	int i;
	for ( i = 0; i <= n - 1; i++)
	{
		if (a[i] <= 'Z'&&a[i] >= 'A')
			a[i] = a[i] + 32;
	}
	for ( i = 0; i <= n-1; i++)
	{
		if (a[i] == 'a' || a[i] == 'e'|| a[i] == 'y' || a[i] == 'i' || a[i] == 'o' || a[i] == 'u')
			continue;
		else
		{
			b[count] = '.';
			b[count + 1] = a[i];
			count += 2;
		}
	}
	printf("%s", b);
	return 0;
}