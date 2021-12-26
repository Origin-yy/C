#include <stdio.h>
int main (void)
{   
    char name1[10],name2[10];

    printf("请输入名字(以空格隔开姓和名）：\n");
    scanf("%s %s",name1,name2);
    printf("\"%s %s\"\n",name1,name2);
    printf("\"%20s %s\"\n",name1,name2);
    printf("\"%s %-20s\"\n",name1,name2);
    printf("   %s %s\n",name1,name2);

    return 0;
}