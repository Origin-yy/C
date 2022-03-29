#include <stdio.h>
int main()
{
	int a,b,i,sum;
	char ch;
	scanf("%d,%d",&a,&b);
	if(a<-100||b>100)
		;
	else{
	for(i=a+1;i<b;i++){
		if(i%7==2)
		sum=sum+i;
	}
	printf("%d",sum);
}
	return 0;
}