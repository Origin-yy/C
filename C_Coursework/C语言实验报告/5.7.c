#include <stdio.h>
#include <string.h>
void input(char a[][20])
{
	int i;
	for(i=0;i<6;i++){
		scanf("%s",a[i]);
	}
}
void sort(char a[][20])
{
	int i,j,r;
	for(i=0;i<6;i++){
		for(j=0;j<5-i;j++){
			r=strcmp(a[i],a[i+1]);
			if(r==1){
				char temp[10]={0};
				strcpy(temp,a[j]);
				strcpy(a[j],a[j+1]);
				strcpy(a[j+1],temp);
			}
		}
	}
}
void output(char a[][20])
{
	int i;
	for(i=0;i<6;i++){
		printf("%s\n",a[i]);
	}
}
int main()
{
    int i = 8;
    char a[i];
	//char a[i][20]={0};
	input(a);
	sort(a);
	output(a);
	return 0;
}