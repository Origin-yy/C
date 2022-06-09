#include <stdio.h>
#include <malloc.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node, *List;

List List_create();
void List_output(List L);
List List_sort(List A, List B);
void List_destroy(List list);

int main()
{
    List A, B, C;
    A = List_create();
    B = List_create();

    C = List_sort(A, B);

    List_output(C);

    free(A);
    free(B);
    List_destroy(C);
    return 0;
}
void List_output(List L)
{
    if (L->next)
    {
        List p;
        p = L->next;
        while (p)
        {
            printf("%d", p->data);
            if (p->next != NULL)
                printf(" ");
            p = p->next;
        }
        printf("\n");
    }
    else
        printf("NULL");
}
List List_create()
{
    //尾插法
    List L, q;
    int x;
    L = (Node *)malloc(sizeof(Node));
    L->data = 0;
    L->next = NULL;
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
List List_sort(List A, List B)
{
    //归并排序
    List C = (List)malloc(sizeof(Node));
    C->data = 0;
    C->next = NULL;
    Node *q = C;
    Node *a = A;
    Node *b = B;
    Node *temp;
    while(a->next)
    {
        a = a->next;
        q->next = a;
        q = a;
        temp = a->next;
        b = b->next;
        q->next = b;
        q = b;
    }
    while(b->next)
    {
        b = b->next;
        q->next = b;
        q = b;
    }
    Node *p = 
    return C;
}

void List_destroy(List list)
{
    Node *cur, *ret;
    ret = list;
    while (ret)
    {
        cur = ret->next;
        free(ret);
        ret = cur;
    }
}