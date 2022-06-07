#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef int DataType;
typedef struct LinkedNode
{
    DataType data;
    struct LinkedNode *prev;
    struct LinkedNode *next;
} LinkedNode;

typedef struct LinkedList
{
    int length;      /* 链表的长度 */
    LinkedNode head; /* 双向循环链表的头节点 */
} LinkedList;

void init_list(LinkedList *list) //初始化链表(带有一个头结点，前后指针指自己)
{
    list->length = 0;
    LinkedNode *temp = (LinkedNode*)malloc(sizeof(LinkedNode));
    list->head = *temp;
    list->head.next = &list->head;
    list->head.prev = &list->head;
    free(temp);
}
LinkedNode *alloc_node(DataType data) //给节点分配内存空间并存储数据，前后指针指空
{
    LinkedNode *L = (LinkedNode *)malloc(sizeof(LinkedNode));
    L->data = data;
    L->prev = NULL;
    L->next = NULL;
    return L;
}
void push_front(LinkedList *list, DataType data) //头插法
{
    LinkedNode *cur = alloc_node(data);
    //当链表只有头结点时
    if (list->head.next == &list->head)
    {
        list->head.prev = cur;    //头结点前指针指cur
        list->head.next = cur;    //头结点后指针指cur
        cur->prev = &list->head;  //cur前指针指头结点
        cur->next = &list->head;  //cur后指针指头结点
    }
    else
    {//顺序不能错
        cur->next = list->head.next; //cur的下一个节点是原来头结点的下一个节点
        list->head.next->prev = cur; //头结点原来的下一个节点的前一个节点是cur
        cur->prev = &list->head;     //cur的前一个节点是头节点
        list->head.next = cur;       //头结点的下一个节点是cur
    }
    list->length++;
}
void push_back(LinkedList *list, DataType data) //尾插法
{
    LinkedNode *cur = NULL;
    //如果链表内只有头结点
    if (list->head.next == &list->head)
    {
        cur = alloc_node(data);   //申请空间，放数据
        list->head.next = cur;    //头结点下一个节点是cur
        cur->prev = &list->head;  //cur前一个节点是头节点
        cur->next = &list->head;  //cur下一个节点是头结点
        list->head.prev = cur;    //头节点前一个节点是cur
    } //如果链表内有其他节点
    else
    {
        cur = alloc_node(data);
        list->head.prev->next = cur;
        cur->prev = list->head.prev;
        list->head.prev = cur;
        cur->next = &list->head;
    }
    list->length++;
}
void traverse(LinkedList *list) //顺序遍历
{
    LinkedNode *cur = list->head.next;
    //如果链表为空
    if (list->length == 0)
    {
    } //啥也不用干
    else
    {
        for (int i = 0; i < list->length; i++)
        {
            printf("%d", cur->data);
            if(i!=list->length-1)
                printf(" ");
            cur = cur->next;
        }
        printf("\n");
    }
}
void traverse_back(LinkedList *list) //倒序遍历
{
    LinkedNode *cur = list->head.prev;
    //如果链表为空
    if (list->length == 0)
    {
    }
    else
    {
        for (int i = 0; i < list->length; i++)
        {
            printf("%d", cur->data);
            if(i!=list->length-1)
                printf(" ");
            cur = cur->prev;
        }
        printf("\n");
    }
}
//自己增加的内容 销毁双向循环链表
void destroy(LinkedList *list)
{
    LinkedNode *cur = list->head.next;
    while (cur != &list->head)
    {
        LinkedNode *ret = cur;
        cur = cur->next;
        free(ret);
    }
}
int main()
{
    int data;
   LinkedList L, *pHead = &L;
    init_list(pHead);
    int flag = 1; //根据输出结果可以观察得到构建链表时头插一次，尾插一次，以此类推
    scanf("%d", &data);
    while (data != -1)
    {
        if (flag)
        {
            push_front(pHead, data);
            flag = 0;
        }
        else
        {
            push_back(pHead, data);
            flag = 1;
        }
        scanf("%d", &data);
    }
    traverse(pHead);
    traverse_back(pHead);
    destroy(pHead); //销毁链表
    return 0;
}