#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;  
static pthread_cond_t cond_pro =PTHREAD_COND_INITIALIZER;
static pthread_cond_t cond_con =PTHREAD_COND_INITIALIZER;

typedef struct SPSCQueue 
{
    char *data;
    int *head;    //循环队列头
    int *rear;    //循环队列尾
    int *num;     //现有产品数量
}SPSCQueue;

//错误函数
void errExitEN(const char *err_string,int line);
//随机生成名为A-Z的产品s
char get_rand_product();
//循环队列初始化
SPSCQueue *SPSCQueueInit(int capacity);      
//生产产品s入队尾 
void SPSCQueuePush(SPSCQueue *queue, void *s); 
//消费产品出队头
void *SPSCQueuePop(SPSCQueue *queue);   
//销毁申请内存
void SPSCQueueDestory(SPSCQueue *); 
//生产者线程           
void *producter_pthread(void*arg);
//消费者线程
void *consumer_pthread(void*arg);

int main(void)
{
    pthread_t pro_tid,con_tid;
    int s;  //判断调用是否成功的标志；
    int capacity = 0;
    printf("请输入仓库内存放产品的最大容量:\n");
    scanf("%d",&capacity);

    SPSCQueue *warehouse =  SPSCQueueInit(capacity);  //得到一个容量为capaci的仓库（队列）
    printf("产品生产和消费开始\n");
    s = pthread_create(&pro_tid, NULL, producter_pthread, warehouse);
    if (s != 0)
        errExitEN("pthread_create",__LINE__);    
    s = pthread_create(&con_tid, NULL, consumer_pthread, warehouse);
    if (s != 0)
        errExitEN("pthread_create",__LINE__); 

    s = pthread_join(pro_tid,NULL);
    if (s != 0)
        errExitEN("pthread_join",__LINE__);
        s = pthread_join(con_tid,NULL);
    if (s != 0)
        errExitEN("pthread_join",__LINE__);
    SPSCQueueDestory(warehouse);
    return 0; 
}
void *producter_pthread(void*arg)
{
    SPSCQueue *warehouse = (SPSCQueue *)arg;
    char product = 0;
    product = get_rand_product();
    while(1)
        SPSCQueuePush(warehouse,&product);  //进行生产操作
}
void *consumer_pthread(void*arg)
{
    SPSCQueue *warehouse = (SPSCQueue *)arg;
    while(1)
        SPSCQueuePop(warehouse);  //进行消费操作
}

void SPSCQueuePush(SPSCQueue *queue, void *s) 
{
    int t;
    char *product = (char*)s;
    t = pthread_mutex_lock(&mtx);
    if(t != 0)
        errExitEN("pthread_mutex_lock",__LINE__);

    while((*queue->rear+1) % sizeof(queue->data) == *queue->head)
    {
        t =pthread_cond_wait(&cond_con,&mtx);
        if(t != 0)
            errExitEN("pthread_cond_wait",__LINE__);
    }
    if((*queue->rear+1) % sizeof(queue->data) != *queue->head)
    {
        queue->data[*queue->rear] = *product;
        *queue->rear= *queue->rear % sizeof(queue->data);
        printf("产品%c被生产了.\n",*product);
        pthread_cond_signal(&cond_pro);
    }
    t = pthread_mutex_unlock(&mtx);
    if (t != 0)
        errExitEN("pthread_mutex_unlock",__LINE__);
}
void *SPSCQueuePop(SPSCQueue *queue)        
{
    int t;
    t = pthread_mutex_lock(&mtx);
    if(t != 0)
        errExitEN("pthread_mutex_lock",__LINE__);

    while(*queue->head == *queue->rear)
    {
        t =pthread_cond_wait(&cond_con,&mtx);
        if(t != 0)
            errExitEN("pthread_cond_wait",__LINE__);
    }
    if(*queue->head != *queue->rear)
    {
        *queue->head= (*queue->head+1) % sizeof(queue->data);
        printf("产品%c被消费了.\n",*queue->head);
        pthread_cond_signal(&cond_pro);
    }
    t = pthread_mutex_unlock(&mtx);
    if (t != 0)
        errExitEN("pthread_mutex_unlock",__LINE__);
}

SPSCQueue *SPSCQueueInit(int capacity)      
{
    SPSCQueue *warehouse = (SPSCQueue*)malloc(sizeof(SPSCQueue));
    warehouse->data = (char*)calloc(capacity,sizeof(char));
    warehouse->head = (int*)calloc(1,sizeof(int));
    warehouse->rear = (int*)calloc(1,sizeof(int));
    warehouse->num = (int*)calloc(1,sizeof(int));
    return warehouse;
}
void SPSCQueueDestory(SPSCQueue *warehouse)
{
    free(warehouse);
    free(warehouse->data);
    free(warehouse->head); 
    free(warehouse->rear);
}
void errExitEN(const char *err_string,int line)
{
    fprintf(stderr,"lint:%d ",line);
    perror(err_string);
    exit(1);
}
char get_rand_product() 
{
    char letter;
	letter = (char)((rand() % 26) + 'A');
	return letter;
}