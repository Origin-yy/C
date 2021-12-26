#include<stdio.h>
#include<ctype.h>
int main(void)
{
	int ch;
	int words = 0, sign = 0, count = 0;
	double average;
	
	while((ch = getchar()) != EOF)
	{	//sign为1理解为读取的字符在单词里。
		//sign为0理解为读取的字符不在单词里。
		if (!isspace(ch) && !sign)
		{
			words++;
			sign = 1;
		}
		if (isalpha(ch))
			count++;
		if (isspace(ch) && sign)	
			sign = 0;
	}
	average = (double)count / (double)words;
	printf("%d 个单词，评价每个单词有 %lf 个字母。\n",count,average);
	
	return 0;
}
