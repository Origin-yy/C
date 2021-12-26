# include <stdio.h>
# include <stdlib.h>
# include <string.h>
 
int main(void)
{
	char ** par_ch ;
	char * words ;
	char tmp_arr_ch[100] ;
	int count ;
 
	printf("How many words do you wish to enter? ");
	scanf("%d" , &count);
	 
	par_ch = (char **)malloc(count * sizeof(char *)) ;
 
	printf("Enter %d words now:\n" , count);
	for (int i = 0 ; i < count ; i++)
	{
		scanf("%s" , tmp_arr_ch);
		words = (char *)malloc((strlen(tmp_arr_ch) + 1) * sizeof(char));
		strcpy(words , tmp_arr_ch);
		par_ch[i] = words ;
	}
 
	puts("Here are your words:");
	for (int i = 0 ; i < count ; i++)
	{
		puts(par_ch[i]);
		free(par_ch[i]);
	}
	free(par_ch);
 
	return 0 ;
}