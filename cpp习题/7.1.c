#include<stdio.h>
#define SPACE ' '
int main(void)
{
    int count_space = 0;
    int count_line_break = 0;
    int count_others = 0;
    int ch;

    printf("Please pit in.\n");
    while (ch = getchar() !='#')
    {
        if(ch  == SPACE)
            count_space++;
        else if(ch == '\n')
            count_line_break++;
        else
            count_others++;
    }
    printf("count_soace:%d  count_line_break:%d  count_others:%d",
            count_space,count_line_break,count_others);
    
    return 0;
}