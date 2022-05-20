#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int cmp(const void*a,const void*b)
{
    return strcmp((char*)a,(char*)b);
}

void input(char a[][100])
{
	printf("请输入6个字符串:\n");
    for(int i=0; i<6; i++)
    {
        scanf("%s",a[i]);
    }
}
  
void sort(char a[][100])
{
	qsort(a,6,100,cmp);
}

void output(char a[][100])
{
    printf("按字典序排序后为:\n");
    for(int i=0; i<6; i++)
    {
        printf("%s\n",a[i]);
    }
}

int main(void)
{
    char a[6][100]={0};
	input(a);
	sort(a);
	output(a);

    return 0;
}