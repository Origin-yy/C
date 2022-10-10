#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100 //最大长度
#define OK 1        //返回值
#define ERROR 0     //返回值
#define OVERFLOW -2

typedef int Status;

typedef struct
{
    char name[20];
    char sex; //'F'表示女性，'M'表示男性
} Person;

typedef struct
{
    Person *base; //队列中数据元素类型为Person
    int front;    //头指针
    int rear;     //尾指针
} SqQueue;

Status InitQueue(SqQueue *Q);                //构造一个空队列Q
Status EnQueue(SqQueue *Q, Person e);        //插入元素e为Q的新的队尾元素
Status DeQueue(SqQueue *Q, Person *e);       //删除Q的队头元素，用e返回其值
Person GetHead(SqQueue Q);                   //返回Q的队头元素，不修改队头指针
Status QueueEmpty(SqQueue Q);                //判断队列是否为空，空则返回1
void DancePartner(Person dancer[], int num); //舞伴问题匹配算法

int main()
{
    Person dancer[MAXSIZE];
    int i, num;
    printf("请输入跳舞总人数：");
    scanf("%d", &num);
    printf("请输入各个跳舞人的姓名和性别（'F'表示女性，'M'表示男性）：\n");
    for (i = 0; i < num; i++)
    {
        printf("请输入第%d个跳舞人的姓名和性别（用空格隔开）：", i + 1);
        scanf("%s %c", &dancer[i].name, &dancer[i].sex);
    }
    DancePartner(dancer, num);
    return 0;
}

Status InitQueue(SqQueue *Q)
{                                                         //构造一个空队列Q
    Q->base = (Person *)malloc(MAXSIZE * sizeof(Person)); //为队列分配一个最大容量为MAXSIZE的数组空间
    if (!Q->base)
        exit(OVERFLOW);     //存储分配失败则返回
    Q->front = Q->rear = 0; //头指针和尾指针置为零，此时队列为空
    return OK;
}

Status EnQueue(SqQueue *Q, Person e) //插入元素e为Q的新的队尾元素
{
    if ((Q->rear + 1) % MAXSIZE == Q->front) //尾指针在循环意义上加1后等于头指针，表明队满
        return ERROR;
    Q->base[Q->rear] = e;              //新元素插入队尾
    Q->rear = (Q->rear + 1) % MAXSIZE; //队尾指针加1
    return OK;
}

Status DeQueue(SqQueue *Q, Person *e) //删除Q的队头元素，用e返回其值
{
    if (Q->front == Q->rear)
        return ERROR;                    //判断队空
    *e = Q->base[Q->front];              //保存队头元素
    Q->front = (Q->front + 1) % MAXSIZE; //队头指针加1
    return OK;
}

Person GetHead(SqQueue Q) //返回Q的队头元素，不修改队头指针
{
    if (Q.front != Q.rear)      //判断队列非空
        return Q.base[Q.front]; //返回队头元素的值，队头指针不变
}

Status QueueEmpty(SqQueue Q) //判断队列是否为空
{
    if (Q.front == Q.rear)
        return OK; //队列空，则返回1
    else
        return ERROR; //队列不空，z则返回0
}

void DancePartner(Person dancer[], int num) // 结构数组dancer中存放跳舞的男女，num是跳舞的人数。
{
    SqQueue Mdancers,
        Fdancers;
    Person p;
    int i;
    InitQueue(&Mdancers); //男士队列初始化
    InitQueue(&Fdancers);
    //女士队列初始化
    for (i = 0; i < num; i++) //根据跳舞者的性别分别入队
    {
        p = dancer[i];
        if (p.sex == 'F')
            EnQueue(&Fdancers, p); //插入女队
        else
            EnQueue(&Mdancers, p); //插人男队
    }
    printf("跳舞的舞伴为:\n");
    while (!QueueEmpty(Fdancers) && !QueueEmpty(Mdancers))
    {                           //依次输出男女舞伴的姓名
        DeQueue(&Fdancers, &p); //女士出队
        printf("%s ", p.name);
        ;                       //输出出队女士姓名
        DeQueue(&Mdancers, &p); //男士出队
        printf("%s\n", p.name); //输出出队男士姓名
    }
    if (!QueueEmpty(Fdancers)) //女士队列非空，输出队头女士的姓名
    {
        p = GetHead(Fdancers); //取女士队头
        printf("女士队伍第一个为: %s\n", p.name);
    }
    else if (!QueueEmpty(Mdancers)) //男士队列非空，输出队头男士的姓名
    {
        p = GetHead(Mdancers); //取男士队头
        printf("男士队伍第一个为: %s\n", p.name);
    }
}