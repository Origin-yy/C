#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;  
static pthread_cond_t cond_pro =PTHREAD_COND_INITIALIZER;
static pthread_cond_t cond_con =PTHREAD_COND_INITIALIZER;

int capacity;

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
    int t;
    SPSCQueue *warehouse = (SPSCQueue *)arg;
    while(1)
    {
        t = pthread_mutex_lock(&mtx);
        if(t != 0)
            errExitEN("pthread_mutex_lock",__LINE__);

        while(*warehouse->num == capacity)
        {
            t =pthread_cond_wait(&cond_con,&mtx);
            if(t != 0)
                errExitEN("pthread_cond_wait",__LINE__);
        }

        if(*warehouse->num != capacity)
        {
            char product = '0';
            product = get_rand_product();
            SPSCQueuePush(warehouse,&product);
        }
        t = pthread_mutex_unlock(&mtx);
        if (t != 0)
            errExitEN("pthread_mutex_unlock",__LINE__);
    }
}
void *consumer_pthread(void*arg)
{
    int t;
    SPSCQueue *warehouse = (SPSCQueue *)arg;
    while(1)
    {
        t = pthread_mutex_lock(&mtx);
        if(t != 0)
            errExitEN("pthread_mutex_lock",__LINE__);

        while(*warehouse->num == 0)
        {
            t =pthread_cond_wait(&cond_pro,&mtx);
            if(t != 0)
                errExitEN("pthread_cond_wait",__LINE__);
        }

        if(*warehouse->num > 0)
        {
            SPSCQueuePop(warehouse);
        }
        t = pthread_mutex_unlock(&mtx);
        if (t != 0)
            errExitEN("pthread_mutex_unlock",__LINE__);
    }

}

void SPSCQueuePush(SPSCQueue *queue, void *s) 
{
    char *product = (char*)s;
    queue->data[*queue->rear] = *product;
    printf("产品%c被生产了.\n",*product);
    *queue->rear= (*queue->rear+1) % capacity;
    (*queue->num)++;
    
    pthread_cond_signal(&cond_pro);
}
void *SPSCQueuePop(SPSCQueue *queue)
{
    printf("产品%c被消费了.\n",queue->data[*queue->head]);
    *queue->head = (*queue->head+1) % capacity;
    (*queue->num)--;

    pthread_cond_signal(&cond_con);
    return NULL;
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
    free(warehouse->data);
    free(warehouse->head); 
    free(warehouse->rear);
    free(warehouse->num);
    free(warehouse);
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