#include <stdio.h>
#include <malloc.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node, *List;

List creat_List();
void output(List H);
List combine_list(List A, List B);
void destroy(List list);

int main()
{
    List A, B, C;
    A = creat_List();
    B = creat_List();

    if (A->data <= B->data)
        C = combine_list(A, B);
    else
        C = combine_list(B, A);

    output(C);
    destroy(C);
    return 0;
}

void output(List L)
{
    Node *p = L;
    if (L->next)
    {
        while (p->next)
        {
            p = p->next;
            printf("%d", p->data);
            if (p->next != NULL)
                printf(" ");
        }
        printf("\n");
    }
    else
        printf("这是一个空链表\n");
}
List creat_List()
{
    //尾插法
    List L;
    Node *q;
    L = (Node *)malloc(sizeof(Node));
    L->next = NULL;

    int x;
    q = L;
    do
    {
        scanf("%d", &x);
        Node *T;
        T = (Node *)malloc(sizeof(Node));
        T->next = NULL;
        T->data = x;

        q->next = T;
        q = T;
        L->data++;
    } while (getchar() != '\n');
    return L;
}

List combine_list(List A, List B)
{
    List C;
    List pa, pb, qa, qb;
    pa = A->next; // pa 指向 A 的第一个结点
    pb = B->next; // pb 指向 B 的第一个节点
    C = A; // 因为 C 中第一个元素是 A 中的元素，所以只需要 C 指向 A 就行了
    while (pa && pb)
    {
        qa = pa;
        qb = pb;
        pa = pa->next;
        pb = pb->next;
        qb->next = qa->next;
        qa->next = qb;
    }
    if (pa == NULL)    // 如果 A 链表的长度小于 B 链表的长度
        qb->next = pb; // 将 B 的后续节点连接到新链表的尾端
    free(B);           //删除 B 的头结点

    return C;
}

void destroy(List L)
{
    Node *p = L;
    Node *T;
    while(p)
    {
        T = p->next;
        free(p);
        p = T;
    }
}