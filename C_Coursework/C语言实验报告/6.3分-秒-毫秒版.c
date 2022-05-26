/*
 *使用windows的童鞋要注意喽！！！
 *1.请在开头加入<windows.h>头文件.
 *2.请把第48行的usleep(10000)改为sleep(1).
 *谢谢合作~
 *(^_^) 
 */
#include <stdio.h>
#include <unistd.h>
int main(void)
{
    int minutes;
    int seconds;
    int millisecond;
    int time = 0;
    printf("请输入一个时间：\n(最长时间为:99:59:99,单位:分:秒:毫秒,)\n");
    scanf("%d:%d:%d", &minutes, &seconds, &millisecond);
    printf("倒计时开始：\n");

    time += minutes * 6000;
    time += seconds * 100;
    time += millisecond;
    printf("%02d:%02d:%02d", minutes, seconds, millisecond);
    fflush(stdout);
    millisecond-=1;

    for (int i = 0; i <= time; i++)
    {
        if (millisecond >= 0)
        {
            printf("\b\b%02d", millisecond);
            millisecond--;
        }
        else if (millisecond == -1 && seconds > 0)
        {
            seconds--;
            millisecond = 99;
            printf("\b\b\b\b\b%02d:%02d", seconds, millisecond);
            millisecond--;
        }
        else if (millisecond == -1 && seconds == 0 && minutes > 0)
        {
            minutes--;
            seconds = 59;
            millisecond = 99;
            printf("\b\b\b\b\b\b\b\b%02d:%02d:%02d", minutes, seconds, millisecond);
            millisecond--;
        }
        fflush(stdout);
        if (i != time)
            usleep(10000);
    }
    printf("\n倒计时结束.\n");
    return 0;
}