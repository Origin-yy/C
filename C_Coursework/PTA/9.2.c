#include <stdio.h>

struct node
{
    int data;
    int next;
} node[100001];

int main(void)
{
    int start, num, temp;
    scanf("%d%d", &start, &num);
    for (int i = 0; i < num; i++)
    {
        scanf("%d", &temp);
        scanf("%d%d", &node[temp].data, &node[temp].next);
    }
    //	printf("\n");
    int a[num];
    a[0] = start;
    for (int i = 1;; i++)
    {
        if (node[a[i - 1]].next == -1)
        {
            num = i;
            break;
        }
        a[i] = node[a[i - 1]].next;
    }
    int flag = -1, x = 0, y = num - 1;
    for (int i = 1; i < num; i++, flag *= -1)
    {
        if (flag == -1)
        {
            node[a[y--]].next = a[x];
        }
        else
        {
            node[a[x++]].next = a[y];
        }
    }
    node[a[x]].next = -1;
    temp = a[num - 1];
    for (int i = 1; i < num; i++)
    {
        printf("%05d %d %05d\n", temp, node[temp].data, node[temp].next);
        temp = node[temp].next;
    }
    printf("%05d %d %d\n", temp, node[temp].data, node[temp].next);
    return 0;
}
