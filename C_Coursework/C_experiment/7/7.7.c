#include <stdio.h>
#include <malloc.h>

typedef struct Node
{
    struct Node *prev;
    int data;
    struct Node *next;
} Node, *List;

List List_creat();
void Node_del(List L, Node *p);
void output(List L);
void List_destroy(List list);

int main()
{
    int m;
    List A;
    A = List_creat();

    printf("请输入m的值:\n");
    scanf("%d", &m);

    int t = 0;
    Node *p = A->next;
    for (int i = 1; A->data >= m; i++)
    {
        if (p == A)
        {
            t++;
            printf("第%d轮报数结束,剩下的小朋友如下:\n",t);
            output(A);
            p = p->next;
            i -= 1;
        }
        else if (i % m == 0)
        {
            Node *q = p->next;
            Node_del(A, p);
            p = q;
        }
        else
            p = p->next;
    }
    printf("报数结束,剩下的小朋友如下:\n");
    output(A);
    List_destroy(A);
    return 0;
}

List List_creat()
{
    List L;
    Node *q;
    L = (Node *)malloc(sizeof(Node));
    L->prev = L;
    L->next = L;
    printf("请输入小朋友的数量：\n");
    scanf("%d", &L->data);

    q = L;
    for (int i = 0; i < L->data; i++)
    {
        Node *T;
        T = (Node *)malloc(sizeof(Node));
        T->prev = NULL;
        T->next = NULL;
        T->data = i + 1;

        q->next = T;
        T->prev = q;
        T->next = L;
        L->prev = T;
        q = T;
    }
    return L;
}

void Node_del(List L, Node *p)
{

    p->next->prev = p->prev;
    p->prev->next = p->next;
    printf("编号为%d的小朋友退出.\n", p->data);
    free(p);
    L->data--;
}

void output(List L)
{
    Node *p;
    p = L;
    if (L->next != L)
    {
        while (p->next != L)
        {
            p = p->next;
            printf("%d", p->data);
            if (p->next != NULL)
                printf(" ");
        }
        printf("\n");
    }
    else
        printf("没有小朋友了\n");
}

void List_destroy(List L)
{
    Node *p = L;
    Node *T;
    while (p != L)
    {
        T = p->next;
        free(p);
        p = T;
    }
}