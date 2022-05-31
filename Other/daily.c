#include<stdio.h>
void put(char** a)
{
    for(int i = 0;i<6; i++)
    {
        printf("%s\n",a[i]);
    }
}
int main()
{
    char *a[6] = {"China","French","America","German","China","China"};
    put(a);
    return 0;
}