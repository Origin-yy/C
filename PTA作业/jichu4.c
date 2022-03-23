#include<stdio.h>

int main()
{
    char a;
    scanf("%c",&a);
    if((int)a>=48&&(int)a<=57)
        printf("%c是数字\n",a);
    else if((int)a>64&&(int)a<91 || (int)a>96&&(int)a<123)
        printf("%c是字母\n",a);
    else
        printf("%c是其他字符",a);

    return 0;
}
