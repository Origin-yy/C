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


    output(C);
    destroy(C);
    return 0;
}

void output(List L)
{
    Node *p;
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