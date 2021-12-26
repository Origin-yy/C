#include<stdio.h>
int main()
{
	printf("请输入指定的次数:");
	int turns;
	scanf("%d",&turns);
	turns=(int)turns;
	float sum1,sum2;
	while(turns>0)
	{
		int i;
		for(sum1=0.0,i=1;i<turns+1;i++)
		{
			sum1+=1.0/i;
		}
		int a;
		for(sum2=0.0,i=1,a=1;i<turns+1;i++)
		{
			sum2+=1.0/i*a;
			a = -1*a;
		}
	float sum;
	sum=sum1+sum2;
	printf("sum1=%f,sum2=%f\n",sum1,sum2);
	printf("The sum of sum1 and sum2 is %f\n",sum);
	printf("请输入另外一个次数:");
	scanf("%d",&turns);
	}
	
	return 0;
}
