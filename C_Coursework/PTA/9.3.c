#include <stdio.h>
#include <malloc.h>

typedef struct LinkNode
{
    int data; //头节点存链表长度，其他节点存数据
    struct LinkNode *next;
} LinkNode, *LinkList;

LinkNode *head = NULL;
LinkNode *end = NULL;

LinkList list_init();                       //创建一个空链表（分配空间和头结点）
void list_add(LinkList L, int k, int data); //第k个节点后插入一个新节点
void list_del(LinkList L, int k);           //删除第k个节点
void list_output(LinkList L);               //从头遍历输出链表
void list_destroy(LinkList L);

int main()
{
    int len, flag, k, data, n;
    LinkList A = list_init();
    scanf("%d", &len);
    for (int i = 0; i < len; i++)
    {
        scanf("%d", &data);
        list_add(A,i,data);
    }
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d",&flag);
        if (flag == 0)
        {
            scanf("%d %d", &k, &data);
            list_add(A, k, data);
        }
        else
        {
            scanf("%d", &k);
            list_del(A, k);
        }
    }
    list_output(A);
    return 0;
}

LinkList list_init() //创建一个空链表（分配空间和头结点）
{
    LinkList L = (LinkList)malloc(sizeof(LinkNode));
    L->data = 0;
    L->next = NULL;
    return L;
}
void list_add(LinkList L, int k, int data) //第k个节点后插入一个新节点
{
    if (k > L->data)
        return;

    LinkNode* T = (LinkNode*)malloc(sizeof(LinkNode));
    T->data = data;

    LinkNode *p = L;
    for (int i = 0; i < k; i++)
        p = p->next;

    if (k != L->data)
        T->next = p->next;
    else
        T->next = NULL;
    p->next = T;
    L->data++;
}
void list_del(LinkList L, int k) //删除第k个节点
{
    if (k == 0 || k > L->data)
        return;

    LinkNode *p = L;
    for (int i = 0; i < k - 1; i++)
        p = p->next;

    if (k != L->data)
    {
        LinkNode *temp = p->next->next;
        free(p->next);
        p->next = temp;
    }
    else
        p->next = NULL;
    L->data--;
}
void list_output(LinkList L) //从头遍历输出链表
{
    if (L->data == 0)
        return;

    LinkNode *t = L->next;
    for (int i = 0; i < L->data; i++)
    {
        printf("%d ", t->data);
        t = t->next;
    }
    printf("\n");
}
