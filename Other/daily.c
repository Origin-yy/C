#include <stdio.h>
#include <malloc.h>
#include "ICmin.h"

int main()
{
    int *a = (int *)malloc(sizeof(int));
    int i = 0;
    int temp;
    FILE *fp = fopen("datafile01.data", "r");
    while (fscanf(fp, "%d", &temp) == 1)
    {
        i++;
        a[i] = temp;
        int *a = realloc(a,sizeof(int)*(i));
        fscanf(fp,"%*c");
    }
    int num =ICntmin(a, i);
    FILE *fp1 = fopen("finaldata.dat","w");
    for(int i = 0; i < 20; i++)
    {
      fprintf("")
    }
}