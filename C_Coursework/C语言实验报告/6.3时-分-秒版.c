/*
 *使用windows的童鞋要注意喽！！！
 *1.请在开头加入<windows.h>头文件.
 *2.请把第48行的usleep(1000000)改为sleep(1000).
 *谢谢合作~
 *(^_^) 
 */
#include <stdio.h>
#include <unistd.h>
int main(void)
{
    int hours;
    int minutes;
    int seconds;
    int time = 0;
    scanf("%d:%d:%d", &hours, &minutes, &seconds);

    time += hours * 3600;
    time += minutes * 60;
    time += seconds;
    printf("%02d:%02d:%02d", hours, minutes, seconds);
    fflush(stdout);
    seconds-=1;
    for (int i = 0; i <= time; i++)
    {
        if (seconds >= 0)
        {
            printf("\b\b%02d", seconds);
            seconds--;
        }
        else if (seconds == -1 && minutes > 0)
        {
            minutes--;
            seconds = 59;
            printf("\b\b\b\b\b%02d:%02d", minutes, seconds);
            seconds--;
        }
        else if (seconds == -1 && minutes == 0 && hours > 0)
        {
            hours--;
            minutes = 59;
            seconds = 59;
            printf("\b\b\b\b\b\b\b\b%02d:%02d:%02d", hours, minutes, seconds);
            seconds--;
        }
        fflush(stdout);
        if (i != time)
            usleep(100000);
    }
    return 0;
}