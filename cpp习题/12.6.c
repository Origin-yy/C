//编写一个程序,生成100个1~10范围内的随机数,并以降序排列(可以把11章的排序算法稍加改动
//便可用于整数排序,这里仅对整数排序)
 
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
 
# define SIZE 100
# define L_LIMIT 1
# define U_LIMIT 100
 
int rnd(int lower , int upper);
void sort(int arr[] , int n);
 
int main(void)
{
	int ar[SIZE] ;
	
	srand((unsigned)time(NULL));
 
	printf("生成的%d个随机数如下:\n" , SIZE);
	for (int i = 0 ; i < SIZE ; i++)
	{
		ar[i] = rnd(L_LIMIT , U_LIMIT);
		printf("%5d " , ar[i]);
		if (((i + 1) % 10) == 0)
			putchar('\n');
	}
 
	sort(ar , SIZE);
	
	printf("\n按降序排列如下:\n");
	for (int i = 0 ; i < SIZE ; i++)
	{
		printf("%5d " , ar[i]);
		if (((i + 1) % 10) == 0)
			putchar('\n');
	}
 
	return 0 ;
}
 
int rnd(int lower , int upper)
{
	int ret_rand ;
 
	ret_rand = (rand() % (upper - lower + 1)) + lower ;
 
	return ret_rand ;
}
 
void sort(int arr[] , int n)
{
	for (int i = 0 ; i < n - 1 ; i++)
		for (int j = 0 ; j < n - i - 1 ; j++)
		{
			if (arr[j] < arr[j + 1])
			{
				int tmp ;
				tmp = arr[j] ;
				arr[j] = arr[j + 1] ;
				arr[j + 1] = tmp ;
			}
		}
}