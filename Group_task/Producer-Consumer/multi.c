#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;  
static pthread_cond_t cond_pro =PTHREAD_COND_INITIALIZER;
static pthread_cond_t cond_con =PTHREAD_COND_INITIALIZER;

int capacity;

typedef struct MPMCQueue
{
    char *data;
    int *head;    //循环队列头
    int *rear;    //循环队列尾
    int *num;     //现有产品数量
}MPMCQueue;

//错误函数
void errExitEN(const char *err_string,int line);
//随机生成名为A-Z的产品s
char get_rand_product();
//循环队列初始化
MPMCQueue *MPMCQueueInit(int capacity);
//生产产品s入队尾 
void MPMCQueuePush(MPMCQueue *queue, void *s,int name);
//消费产品出队头
void *MPMCQueuePop(MPMCQueue *queue,int name);
//销毁申请内存
void MPMCQueueDestory(MPMCQueue *);
//生产者线程           
void *producter_pthread(void*arg);
//消费者线程
void *consumer_pthread(void*arg);

int main(void)
{
    int num_pro,num_con;
    int s;  //判断调用是否成功的标志；
    printf("请输入仓库内存放产品的最大容量:\n");
    scanf("%d",&capacity);
    printf("请输入生产者和消费者的数量：\n");
    scanf("%d %d",&num_pro,&num_con);

    pthread_t pro_tid[num_pro];
    pthread_t con_tid[num_con];

    MPMCQueue *warehouse =  MPMCQueueInit(capacity);  //得到一个容量为capaci的仓库（队列）

    printf("产品生产和消费开始\n");
    for(int i=0; i<num_pro; i++)
    {
        s = pthread_create(&pro_tid[i], NULL, producter_pthread, warehouse);
        if (s != 0)
            errExitEN("pthread_create",__LINE__);   
    }
    for(int i=0; i<num_con; i++)
    {
        s = pthread_create(&con_tid[i], NULL, consumer_pthread, warehouse);
        if (s != 0)
            errExitEN("pthread_create",__LINE__); 
    }
    
    for(int i=0; i<num_pro; i++)
    {
        s = pthread_join(pro_tid[i],NULL);
        if (s != 0)
            errExitEN("pthread_join",__LINE__);
    }
    for(int i=0; i<num_con; i++)
    {
        s = pthread_join(con_tid[i],NULL);
        if (s != 0)
            errExitEN("pthread_join",__LINE__);
    }
    MPMCQueueDestory(warehouse);
    return 0; 
}
void *producter_pthread(void*arg)
{
    int t;
    pthread_t tid = 0;
    tid = pthread_self();
    MPMCQueue *warehouse = (MPMCQueue *)arg;
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
            MPMCQueuePush(warehouse,&product,tid);
        }
        t = pthread_mutex_unlock(&mtx);
        if (t != 0)
            errExitEN("pthread_mutex_unlock",__LINE__);
    }
}
void *consumer_pthread(void*arg)
{
    int t;
    pthread_t tid = 0;
    tid = pthread_self();
    MPMCQueue *warehouse = (MPMCQueue *)arg;
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
            MPMCQueuePop(warehouse,tid);
        }
        t = pthread_mutex_unlock(&mtx);
        if (t != 0)
            errExitEN("pthread_mutex_unlock",__LINE__);
    }
}

void MPMCQueuePush(MPMCQueue *queue, void *s,int name) 
{
    char *product = (char*)s;
    queue->data[*queue->rear] = *product;
    printf("生产者%d生产了产品%c.\n",name,*product);
    *queue->rear= (*queue->rear+1) % capacity;
    (*queue->num)++;
    
    pthread_cond_signal(&cond_pro);
}
void *MPMCQueuePop(MPMCQueue *queue,int name)
{
    printf("消费者%d消费了产品%c.\n",name,queue->data[*queue->head]);
    *queue->head = (*queue->head+1) % capacity;
    (*queue->num)--;

    pthread_cond_signal(&cond_con);
    return NULL;
}

MPMCQueue *MPMCQueueInit(int capacity)
{
    MPMCQueue *warehouse = (MPMCQueue*)malloc(sizeof(MPMCQueue));
    warehouse->head = (int*)calloc(1,sizeof(int));
    warehouse->data = (char*)calloc(capacity,sizeof(char));
    warehouse->rear = (int*)calloc(1,sizeof(int));
    warehouse->num = (int*)calloc(1,sizeof(int));
    return warehouse;
}
void MPMCQueueDestory(MPMCQueue *warehouse)
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