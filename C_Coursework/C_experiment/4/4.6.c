#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct grade //结构体记录一个人的成绩和序号
{
    int num;
    int score;
} a[100];

int cmp(const void *a, const void *b)
{
    if (((struct grade *)a)->score != ((struct grade *)b)->score)
        return ((struct grade *)b)->score - ((struct grade *)a)->score;
    else
        return ((struct grade *)a)->num - ((struct grade *)b)->num;
}

int main(void)
{
    int n = 0, r = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i].score);
        a[i].num = i + 1;
    }

    qsort(a, n, sizeof(a[0]), cmp);
    //打印输出，t用来存前面已有多少对成绩相等的人数（每次出现不相等的成绩则置为0）
    int t = 0;
    for (int i = 0; i < n; i++)
    {
        if (i > 0 && a[i - 1].score == a[i].score)
        {
            t++;
            printf("%d:%d,%d\n", i + 1 - t, a[i].num, a[i].score); //当前成绩名次原本为i+1名，如果当前成绩和上一个成绩相等，t加1，当前成绩的最终名次应为原本名次（i+1）减去已经有多少对成绩相同的人数（t）即i+1-1-t
        }
        else
        {
            t = 0;
            printf("%d:%d,%d\n", i + 1, a[i].num, a[i].score); //当前成绩名次原本为i+1名，如果当前成绩和上一个成绩不相等，直接打印第i+1名，并将已存的t置为0
        }
    }
    return 0;
}