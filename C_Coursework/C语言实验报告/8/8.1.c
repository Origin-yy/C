#include <stdio.h>
#include <stdlib.h>

int cmp(const void* a,const void* b)
{
    return *(int*)a - *(int*)b;
}
int main()
{
    FILE *p1, *p2,*p3;
    char a[2000];
    char ch;
    int i = 0;
    p1 = fopen("./string1.txt", "r");
    p2 = fopen("./string2.txt", "r");
    ch = fgetc(p1);
    while(ch != '\n')
    {
        a[i++] = ch;
        
    }
    while(ch = fgetc(p2) != '\n')
        a[i++] = ch;
    qsort(a,i,sizeof(char),cmp);
    p3 = fopen("./result1","w");
    fwrite(a,sizeof(char),i,p3);
    return 0;
}
