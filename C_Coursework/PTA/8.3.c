#include <stdio.h>

typedef struct informaiton
{
    int id;
    char name[20];
    char profession;
    char title[20];
}informaiton;
int main()
{
    int n;
    scanf("%d",&n);
    informaiton staff[n];
    int nt = 0,nw = 0;
    for(int i=0; i<n; i++)
    {
        scanf("%d %s %c %[^\n]",&staff[i].id,staff[i].name,&staff[i].profession,staff[i].title);
        printf("%d %s %c %s\n",staff[i].id,staff[i].name,staff[i].profession,staff[i].title);
        if(staff[i].profession == 'w')
            nw++;
        else
            nt++;
    }
    printf("tcount = %d, wcount = %d\n",nt,nw);
    return 0;
}