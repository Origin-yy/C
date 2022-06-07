#include <stdio.h>

int N, k = 0; // N为节点个数，将其设为全局变量方便递归是函数的调用
typedef struct
{
    int Data;
    int Address; 
    int Next;
} LinkNode, *LinkList;

void Link(int address, LinkNode *a, LinkNode *t) //将结点按顺序存入a中
{
    int i;
    for (i = 0; i < N; i++)
    {
        if (t[i].Address == address) //找到第一个节点，将其放入a，之后递归放其他的节点
        {
            a[k++] = t[i];
            break;
        }
    }
    if (t[i].Next != -1)
        Link(t[i].Next, a, t); //递归，对其他节点进行同样操作
}

int main()
{
    int A; //首结点的地址
    scanf("%d %d", &A, &N);
    LinkNode a[N], b[N], t[N]; // t为第一序列，a为第二序列，b为第三序列
    for (int i = 0; i < N; ++i)
        scanf("%d %d %d",&t[i].Address,&t[i].Data,&t[i].Next);

    Link(A, a, t);        //这里第一个待寻找的地址参数用A，找到第一个结点
    int m = 0, n = N - 1; //两个指针，m指向a中首结点，n指向a中尾结点
    int j = 0;            //计数器（下标）
    while (j < N)         // a序列->b序列
    {
        b[j++] = a[n--];
        if (j < N)
            b[j++] = a[m++];
    }

    for (int i = 0; i < N - 1; ++i)
        b[i].Next = b[i + 1].Address; //将各相邻节点以地址形式相连
    b[N - 1].Next = -1; //末尾结点的Next设为 - 1
    
    for (int i = 0; i < N; ++i)
    {
        if(b[i].Next != -1)
            printf("%05d %d %05d\n",b[i].Address,b[i].Data,b[i].Next);
        else
            printf("%05d %d %d\n",b[i].Address,b[i].Data,b[i].Next);
    }
    return 0;
}
