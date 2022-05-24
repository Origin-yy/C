#include <stdio.h>
#include <string.h>

typedef struct information
{
    char name[50];
    int id;
    int Chinese;
    int Math;
    int English;
} information;

int MAX_NUM = 100;

//学生信息初始化函数
void information_init(information *students);

//学生信息录入函数
void information_input(information *students,int num);

//学生信息排序函数
void information_sort(information *students,int num);

//学生信息查询函数
void information_output(information *students,int num);

//计算平均值函数
void average(information *students,int num);

int main(void)
{
    int flag = -1;
    int num = 0;
    information students[MAX_NUM];
    information_init(students);
    printf("比温馨提示还要温馨的提示：\n"
           "本程序最多只支持保存100名学生的信息哦~\n");
    printf("请您先输入一些学生的成绩：\n");
    information_input(students,num);

    while(1)
    {
        printf("请选择您想进行的操作:\n1.学生成绩录入    2.学生成绩排序\n"
                               "3.学生成绩查询    4.计算平均值\n"
                               "5.退出程序\n输入操作前的序号即可:");
        scanf("%d",&flag);

        if(flag == 1)
            information_input(students,num);
        else if(flag == 2)
            information_sort(students,num);
        else if(flag == 3)
            information_output(students,num);
        else if(flag == 4)
            average(students,num);
        else if(flag == 5)
        {
            printf("非常感谢您使用本程序，期待与您的下次相遇,再会(^_^)\n");
            break;
        }
        else
        {
            printf("拜托,让你输入序号1、2、3、4啦,这你都能输错,好吧,再给你一次机会\n");
            continue;
        }
    }
    return 0;
}

//学生信息初始化函数
void information_init(information *students)
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
void information_input(information *students,int num)
{
    printf("您需要输入几名学生的信息那？(输入一个数字即可)\n")
        printf("您需要输入几名学生的信息那？(输入一个数字即可)\n");
}

//学生信息排序函数
void information_sort(information *students,int num)
{

}

//学生信息查询函数
void information_output(information *students,int num)
{

}

//计算平均值函数
void average(information *students,int num)
{

}
