#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>

#define MAXSIZE 10
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;  
static pthread_cond_t cond_pro =PTHREAD_COND_INITIALIZER;
static pthread_cond_t cond_con =PTHREAD_COND_INITIALIZER;

typedef struct data
{
    char* data[MAXSIZE];
    int head;    //循环队列头
    int rear;    //循环队列尾
    int num;     //现有产品个数
}data;

data warehouse = {'\0',0,0,0};

void errExitEN(const char *err_string,int line)
{
    fprintf(stderr,"lint:%d ",line);
    perror(err_string);
    exit(1);
}

char get_rand_product() //随机生成名为A~Z的产品
{
    char letter;
	letter = (char)((rand() % 26) + 'A');
	return letter;
}

void *producter(void*arg)
{
    int s;
    s = pthread_mutex_lock(&mtx);
    if(s != 0)
        errExitEN("pthread_mutex_lock",__LINE__);

    while(warehouse.num == MAXSIZE)
    {
        s =pthread_cond_wait(&cond_con,&mtx);
        if(s != 0)
            errExitEN("pthread_cond_wait",__LINE__);
    }
    whlie(warehouse.num<MAXSIZE)
    {
        warehouse.data[warehouse.rear] = get_rand_product();
        warehouse.rear = (warehouse.rear+1)%MAXSIZE;
        warehouse.num++;
    }
}

void *consumer(void*arg)
{
    
}

void SPSCQueueDestory(data *pool)
{
    
}

int main(void)
{
    pthread_t pro_tid,con_tid;
    int s;  //判断调用是否成功的标志；

    s = pthread_create(&pro_tid, NULL, producter, NULL);
    if (s != 0)
        errExitEN("pthread_create",__LINE__);    
    s = pthread_create(&con_tid, NULL, consumer, NULL);
    if (s != 0)
        errExitEN("pthread_create",__LINE__); 

    printf("产品生产和消费开始\n");

    s = pthread_join(pro_tid,NULL);
    if (s != 0)
        errExitEN("pthread_join",__LINE__);
        s = pthread_join(con_tid,NULL);
    if (s != 0)
        errExitEN("pthread_join",__LINE__);

    return 0; 
}
