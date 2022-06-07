#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
	int date;
	struct node* next;
}node,*list;
void suan(list a,int*max,int*min,double*average);
int main()
{
	int x,max,min;
	double average;
	list head=(list)malloc(sizeof(node));
	head->next=NULL;
	list p=NULL,q;
	q=head;
	do{
		list p=(list)malloc(sizeof(node));
		scanf("%d",&x);
		p->date=x;
		p->next=q->next;
		q->next=p;
		q=p;
	}while(p&&getchar()!='\n');
	suan(head,&max,&min,&average);
	printf("最大值为%d\n最小值为%d\n平均值为%lf\n",max,min,average);
	return 0;
}
void suan(list a,int*max,int*min,double*average)
{
	int count=0;
	list p=a->next;
	*max=p->date;
	*min=p->date;
	double sum=0.0;
	while(p){
		if(*max<p->next->date){
		   *max=p->next->date;
		   p=p->next;
	    }
	    if(*min>p->next->date){
		   *min=p->next->date;
		   p=p->next;
	    }
	}
    while(p){
    	sum+=p->date;
    	count++;
    	p=p->next;
	} 
	*average=sum/count;
}
