#include <stdio.h>

int ICntmin(int *p, int num)
{
    int temp;
    int t = 0;
    for(int i = 1; i<num; i++)
    {
        int flag = 0;
        for(int j = 0; j<num-1 - i; j++)
        {
            if(p[j] > p[j+1])
            {
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
                flag = 1;
            }
        }
        if(flag == 0)
            break;
    }
    
    for(int i = 0; i < 20; i++)
    {
        if( p[i] % 15 == 0 )
            t++;
    }
    return t;
}