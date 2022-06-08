//windows加<window.h>头文件，sleep(1000000)改为Sleep(1000)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
//#include <windows.h>
typedef struct Node
{
    char name[50];
    int id;
    int Chinese;
    int Math;
    int English;
    struct Node *next;
} Node,*List;

int MAX_NUM = 100;

//排序函数
int cmp(const void*a,const void* b);
//学生信息初始化函数
void List_init(Node *students);

//学生信息录入函数
void Node_input(Node *students, int *num);

//学生信息排序函数
void List_sort(Node *students, int *num);

//学生信息查询函数
void List_output(Node *students, int *num);

//计算平均值函数
void average(Node *students, int *num);

int main(void)
{
    int flag = -1;
    int num = 0;
    Node students[MAX_NUM];
    Node_init(students);
    printf("Hi,我是小爱，是一个简单的学生信息管理系统,我还有很多不足,请温柔地使用我~\n\n");
    printf("比温馨提示还要温馨的提示:\n"
           "小爱最多只支持保存100名学生的信息哦~\n\n");

    printf("请您先输入一些学生的成绩:\n");
    Node_input(students, &num);

    while (1)
    {
        printf("请选择您想进行的操作:\n1.学生成绩录入    2.学生成绩排序\n"
               "3.学生成绩查询    4.计算平均值\n"
               "5.退出程序\n输入操作前的序号即可:");
        scanf("%d", &flag);
        printf("\n");
        if (flag == 1)
            Node_input(students, &num);
        else if (flag == 2)
            Node_sort(students, &num);
        else if (flag == 3)
            Node_output(students, &num);
        else if (flag == 4)
            average(students, &num);
        else if (flag == 5)
        {
            printf("你要走了吗≥﹏≤\n");
            //Sleep(1000);
            usleep(1000000);
            printf("你不要走好不好~\n");
            //Sleep(1000);
            usleep(1000000);
            printf("我知道...\n");
            //Sleep(1000);
            usleep(1000000);
            printf("作为一个程序\n");
            //Sleep(1000);
            usleep(1000000);
            printf("被使用完就会被无情地抛弃\n");
            //Sleep(1000);
            usleep(1000000);
            printf("这就是我的宿命......\n");
            //Sleep(1000);
            usleep(1000000);
            printf("我知道我留不住你(失落）...\n");
            //Sleep(1000);
            usleep(1000000);
            printf("那.....下次运行再见吧\n");
            //Sleep(1000);
            usleep(1000000);
            printf("什么?不想看到这一大堆废话,那你不会摁下Ctrl+C吗?\n");
            //Sleep(1000);
            usleep(1000000);
            break;
        }
        else
        {
            printf("拜托,让你输入序号1、2、3、4、5啦,这你都能输错,好吧,再给你一次机会\n");
            continue;
        }
    }
    return 0;
}

//学生信息初始化函数
void List_init(Node *students)
{
    for (int i = 0; i < MAX_NUM; i++)
    {
        memset(students[i].name, 0, 50);
        students[i].id = 0;
        students[i].Chinese = 0;
        students[i].Math = 0;
        students[i].English = 0;
    }
}

//读入学生信息函数
void Node_input(Node *students, int *num)
{
    printf("您需要输入几名学生的信息呢？(输入一个数字即可)\n");
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        printf("请输入第%d学生的信息:\n", i+1);
        printf("学号:");
        while (scanf("%d", &students[i + *num].id) == 0 || students[i + *num].id > 100000000 || students[i + *num].id < 1)
        {
            printf("十分抱歉,本程序的学号范围是1-100000000哦~,请您重新输入.");
            printf("学号:");
            continue;
        }
        printf("姓名:");
        while (scanf("%s", students[i + *num].name) == 0)
            continue;
        printf("语文:");
        while (scanf("%d", &students[i + *num].Chinese) == 0 || students[i + *num].Chinese > 100 || students[i + *num].Chinese < 0)
        {
            printf("十分抱歉,本程序的课程分数范围是0-100哦~,请您重新输入成绩.\n");
            printf("语文:");
            continue;
        }
        printf("数学:");
        while (scanf("%d", &students[i + *num].Math) == 0 || students[i + *num].Math > 100 || students[i + *num].Math < 0)
        {
            printf("十分抱歉,本程序的课程分数范围是0-100哦~,请您重新输入成绩.\n");
            printf("数学:");
            continue;
        }
        printf("英语:");
        while (scanf("%d", &students[i + *num].English) == 0 || students[i + *num].English > 100 || students[i + *num].English < 0)
        {
            printf("十分抱歉,本程序的课程分数范围是0-100哦~,请您重新输入成绩.\n");
            printf("英语:");
            continue;
        }
        printf("\n");
    }
    *num += n;
}

//学生信息排序函数
void List_sort(Node *students, int *num)
{
    qsort(students,*num,sizeof(Node),cmp);
    printf("已按照三门课程的平均成绩对学生进行排序\n\n");
}

//学生信息查询函数
void List_output(Node *students, int *num)
{
    printf("已录入的学生信息如下:\n\n");
    for (int i = 0; i < *num; i++)
    {
        printf("第%i名学生:\n", i+1);
        printf("学号：%d\n", students[i].id);
        printf("姓名：%s\n", students[i].name);
        printf("语文：%d\n", students[i].Chinese);
        printf("数学：%d\n", students[i].Math);
        printf("英语：%d\n\n", students[i].English);
    }
    printf("已录入的学生信息展示完毕\n\n");
}

//计算平均值函数
void average(Node *students, int *num)
{
    int sum[3] = {0,0,0};
    for(int i=0; i<*num; i++)
    {
        sum[0] += students[i].Chinese;
        sum[1] += students[i].Math;
        sum[2] += students[i].English;
    } 
    printf("已录入学生的语文平均成绩为:%.3lf\n",(double)sum[0]/3);
    printf("已录入学生的数学平均成绩为:%.3lf\n",(double)sum[1]/3);
    printf("已录入学生的英语平均成绩为:%.3lf\n\n",(double)sum[2]/3);
    printf("(以上平均成绩均保留三位有效数字)\n\n");
}

int cmp(const void*a,const void* b)
{
    Node c = *(Node*)a;
    Node d = *(Node*)b;
    int t = (d.Chinese + d.Math + d.English) - (c.Chinese + c.Math + c.English);
    if(t != 0)
        return t;
    else
        return c.id - d.id;
}
