#include <stdio.h>
int main()

{

    char p[] ="hello,world";

    char* p1 ="hello,world";

    char* p2 ="hello,world";

    printf("%d\n",p == p1);

    printf("%d\n",p2 == p1);

    printf("%d\n",p == p2);
    printf("%lu\n",sizeof(p));

    printf("%lu\n",sizeof(p1));

    printf("%lu\n",sizeof(p2));
 

    return 0;

}