#include <stdio.h>

typedef struct stu
{
    int id;
    double score;
} stu;
void sort(stu *ps, int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (ps[j].score < ps[j + 1].score)
            {
                stu t = ps[j];
                ps[j] = ps[j + 1];
                ps[j + 1] = t;
            }
            else if (ps[j].score == ps[j + 1].score && ps[j].id > ps[j + 1].id)
            {
                stu t = ps[j];
                ps[j] = ps[j + 1];
                ps[j + 1] = t;
            }
}
int main(void)
{
    int n;
    scanf("%d", &n);
    stu student[n];
    for (int i = 0; i < n; i++)
        scanf("%d %lf", &student[i].id, &student[i].score);
    sort(student, n);
    for (int i = 0; i < n; i++)
    {
        int t = 0;
        if (i > 0 && student[i].score == student[i - 1].score)
        {
            t++;
            printf("%d %d %.2lf", i + 1 - t, student[i].id, student[i].score);
        }
        else
        {
            t = 0;
            printf("%d %d %.2lf", i + 1, student[i].id, student[i].score);
        }
        if (i != n - 1)
            printf("\n");
    }
    return 0;
}