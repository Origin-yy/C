#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>

#define NONE           "\e[0m"
#define BLACK          "\e[0;30m"
#define L_BLACK        "\e[1;30m"
#define RED            "\e[0;31m"
#define L_RED          "\e[1;31m"
#define GREEN          "\e[0;32m"
#define L_GREEN        "\e[1;32m"
#define YELLOW         "\e[0;33m"
#define L_YELLOW       "\e[1;33m"
#define BLUE           "\e[0;34m"
#define L_BLUE         "\e[1;34m"
#define PURPLE         "\e[0;35m"
#define L_PURPLE       "\e[1;35m"
#define D_GREEN        "\e[0;36m"
#define L_D_GREEN      "\e[1;36m"
#define WHITE          "\e[0;37m"
#define L_WHITE        "\e[1;37m"

typedef struct Node
{
    int id;
    char name[50];
    char sex;
    int Chinese;
    int Math;
    int English;
    struct Node *next;
} Node, *List;

int MAX_NUM = 100;

//展示操作选项
void display_options();

//创建一个空链表
List List_init();

//输入学生信息
void Node_insert(List L);

//删除学生信息
void Node_delete(List L);

//修改学生信息
void Node_change(List L);

//排序学生信息
void List_sort(List L);

//展示学生信息
void List_output(List L);

//读取学生信息
void List_output(List L);

//保存学生信息
void List_output(List L);

//链表销毁
void destroy(List L);

int main(void)
{
    int flag = -1;
    List L = List_init();

    display_options();
    
    while(1)
    {
        printf("请输入您想进行的操作的序号: \n");
        scanf("%d", &flag);
        switch(flag)
        {
            case 0:
                printf("感谢您的使用，再见。\n");
                exit(0);
            case 1:
                Node_insert(L);
                break;
            case 2:
                Node_delete(L);
                break;
            case 3:
                Node_change(L);
                break;
            case 4:
                List_sort(L);
                break;
            case 5:
                List_output(L);
                break;
            case 6:
                List_output(L);
                break;
            case 7:
                List_output(L);
                break;
            case 8:
                display_options();
                break;
            default:
                printf("输入有误，请重新输入。\n");
                continue;
        }
        printf("\n");
    }
    destroy(L);
    return 0;
}

void display_options()
{
    printf(L_RED"欢迎使用学生管理系统!。\n\n");
    printf(L_YELLOW "************************学生管理系统*************************\n"NONE);
	printf(L_GREEN  "***---------------------------*---------------------------***\n"NONE);
	printf(L_BLUE   "*  1、输入学生信息     2、删除学生信息     3、修改学生信息  *\n"NONE);	
	printf(L_PURPLE "*  4、排序学生信息     5、展示学生信息     6、读取学生信息  *\n"NONE);
	printf(L_D_GREEN"*  7、保存学生信息     8、显示操作选项     0、退出管理系统  *\n"NONE);
	printf(L_GREEN  "***---------------------------*---------------------------***\n"NONE);
	printf(L_YELLOW "*************************************************************\n"NONE);
}

//创建一个空链表
List List_init()
{
    List L = (List)malloc(sizeof(Node));
    L->id = 0;
    L->next = NULL;
    return L;
}

//输入学生信息
void Node_insert(List L)
{
    printf("希望录入的学生信息数量为：\n");
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        Node *T = (Node *)malloc(sizeof(Node));

        Node *p = L;
        while (p->next)
            p = p->next;

        printf("请输入第%d学生的信息:\n", i + 1);
        printf("学号:");
        while (!scanf("%d", &T->id) || T->id > 100000000 || T->id < 1)
        {
            printf("学号范围是1-100000000,请重新输入.");
            printf("学号:");
            continue;
        }
        printf("姓名:");
        while (!scanf("%s", T->name))
            continue;
        printf("性别:");
        getchar();
        getchar();
        while (!scanf("%c\n", &T->sex)  || T->sex != 'm'  || T->sex != 'w')
        {
            printf("请输入m(男)/w(女)\n");
            continue;
        }
        printf("语文:");
        while (!scanf("%d", &T->Chinese) || T->Chinese > 100 || T->Chinese < 0)
        {
            printf("课程分数范围是0-100,请重新输入成绩.\n");
            printf("语文:");
            continue;
        }
        printf("数学:");
        while (!scanf("%d", &T->Math) || T->Math > 100 || T->Math < 0)
        {
            printf("课程分数范围是0-100,请重新输入成绩.\n");
            printf("数学:");
            continue;
        }
        printf("英语:");
        while (!scanf("%d", &T->English) || T->English > 100 || T->English < 0)
        {
            printf("课程分数范围是0-100,请重新输入成绩.\n");
            printf("英语:");
            continue;
        }
        printf("\n");
        p->next = T;
        T->next = NULL;
        p = T;
    }
    L->id += n;
}

//删除学生信息
void Node_delete(List L)
{

}

//修改学生信息
void Node_change(List L)
{

}

//排序学生信息
void List_sort(List L)
{
    Node *a, *b, temp;
    if (L->next == NULL)
    {
        printf("当前没有学生信息,请先输入一些学生信息.\n\n");
        return;
    }
    if (L->next->next == NULL)
    {
        printf("当前只有一个学生信息,无需排序.\n\n");
        return;
    }
    a = L->next;
    while (a->next)
    {
        b = a->next;
        while (b)
        {
            if ((a->Chinese + a->Math + a->English) < (b->Chinese + b->Math + b->English))
            {
                temp = *a;
                *a = *b;
                *b = temp;
                temp.next = a->next;
                a->next = b->next;
                b->next = temp.next;
            }
            b = b->next;
        }
        a = a->next;
    }
    printf("已按照三门课程的平均成绩对学生进行排序\n\n");
}

//展示学生信息
void List_output(List L)
{
    Node *p = L;
    int i = 1;
    printf("已有的学生信息如下:\n\n");
    printf(L_YELLOW "*********************************************************************\n"NONE);
    printf(L_BLUE   "*   序号|   学号|   姓名|   性别|   语文|   数学|   英语|   均分|   *\n"NONE);
    while (p->next)
    {
        p = p->next;
        printf(L_YELLOW"*"NONE);
        printf("%7d|", i);
        printf("%7d|", p->id);
        printf("%7s|", p->name);
        printf("%7c|", p->sex);
        printf("%7d|", p->Chinese);
        printf("%7d|", p->Math);
        printf("%7d|", p->English);
        printf("%7.3lf|", (double)(p->Chinese + p->Math + p->English)/3);
        printf(L_YELLOW"   *\n\n"NONE);
        i++;
    }
    printf("已录入的学生信息展示完毕\n\n");
}
//销毁链表
void destroy(List L)
{
    Node *p = L;
    Node *T;
    while (p)
    {
        T = p->next;
        free(p);
        p = T;
    }
}