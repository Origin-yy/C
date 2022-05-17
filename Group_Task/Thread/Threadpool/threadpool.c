#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>

//任务结构体
typedef struct Task
{
    void(*function)(void* arg);  //任务函数
    void* arg;                   //任务函数的参数
}Task;

//线程池结构体
typedef struct ThreadPool
{
    Task* task_queue;  //任务队列
    int capacity;      //任务队列的容量
    int size;          //当前任务个数
    int front;         //队头
    int rear;          //队尾

    int min_num;             //最小线程数量
    int max_num;             //最大线程数量
    int busy_num;            //正在处理任务的线程数量
    int live_num;            //存活的线程数量
    int exit_num;            //将要销毁的线程数量

    pthread_t manager_tids;   //管理者线程ID
    pthread_t *workers_tids;   //工作的线程ID

    pthread_mutex_t mutex_pool;   //整个线程池的互斥锁
    pthread_mutex_t mutex_busy;   //busy_num的互斥锁
    pthread_cond_t cond_notfull;  //阻塞到任务队列不满的条件变量
    pthread_cond_t cond_notempty; //阻塞到任务队列不空的条件变量

    int shut_down;       //是不是要销毁线程池，销毁为1；不销毁为0
} ThreadPool;

int NUMBER = 2;   //每次管理者增/删的线程数（为2）

//创建并初始化线程
ThreadPool *threadpool_create(int min, int max, int size);

//销毁线程池
int threadpool_destroy(ThreadPool* pool);

//给线程池的任务队列里添加任务
void threadpool_addtask(ThreadPool* pool, void(*func)(void*), void* arg);

//获取线程池中工作的线程个数
int threadpool_busynum(ThreadPool* pool);

//获取线程池中活着的线程个数
int threadpool_alivenum(ThreadPool* pool);

//工作者线程（从任务队列里取任务并完成）
void* worker(void* arg);

//管理者线程（增删工作者线程）
void* manager(void* arg);

//线程池中的单个线程退出
void thread_exit(ThreadPool* pool);

//任务函数
void task_func(void* arg);


int main(void)
{
    ThreadPool* pool = threadpool_create(5,15,100);
    for (int i=0; i<100; i++)
    {
        char *task_name = (char*)malloc(sizeof(char));
        *task_name = (char)((rand() % 26) + 'A');
        threadpool_addtask(pool, task_func, task_name);
        printf("任务%c被添加到任务队列中.\n",*task_name);

        if(task_name != NULL)
        {
            free(task_name);
            task_name = NULL;
        }
    }

    sleep(20);

    threadpool_destroy(pool);
    return 0;
}

void task_func(void* arg)
{
    char task_name = *(char*)arg;
    printf("工作者线程%d正在进行任务%c.",pthread_self(),task_name);
    sleep(1);
}

//创建并初始化线程
ThreadPool *threadpool_create(int min, int max, int size)
{
    ThreadPool* pool = (ThreadPool*)malloc(sizeof(ThreadPool));
    do
    {
        if(pool == NULL)
        {
            printf("线程池申请堆内存失败.\n");
            break;
        }

        pool->workers_tids = (pthread_t*)calloc(sizeof(pthread_t),max);
        if(pool->workers_tids == NULL)
        {
            printf("工作者线程ID数组申请堆内存失败.\n");
            break;
        }
        
        //线程池相关内容初始化
        pool->min_num = min;
        pool->max_num = max;
        pool->busy_num = 0;
        pool->live_num = min;   //初始创建最小工作者线程个数个工作者线程
        pool->exit_num = 0;

        if (pthread_mutex_init(&pool->mutex_pool,NULL) != 0 || 
            pthread_mutex_init(&pool->mutex_busy,NULL) != 0 ||
            pthread_cond_init(&pool->cond_notempty,NULL) != 0 ||
            pthread_cond_init(&pool->cond_notfull, NULL) != 0)
        {
            printf("互斥量或条件变量初始化失败.\n");
            break;
        }

        // 任务队列相关内容初始化
        pool->task_queue = (Task*)malloc(sizeof(Task) * size);
        pool->capacity = size;
        pool->size = 0;
        pool->front = 0;
        pool->rear = 0;

        pool->shut_down = 0;

        // 创建管理者线程和工作者线程
        pthread_create(&pool->manager_tids, NULL, manager, pool);
        for (int i = 0; i < min; i++)
        {
            pthread_create(&pool->workers_tids[i], NULL, worker, pool);
        }
        return pool;
    } while (0);

    //如果do-while循环中申请堆内存全部成功，函数会返回一个线程池指针并退出，不会运行以下代码
    // 如果前面的do—while是break出来，说明申请堆内存时出错，没有返回线程池的指针，
    // 进行以下步骤释放申请成功的堆内存
    if (pool && pool->workers_tids)
    { 
        free(pool->workers_tids);
        pool->workers_tids = NULL;
    }
    if (pool && pool->task_queue) 
    {
        free(pool->task_queue);
        pool->task_queue = NULL;
    }
    if (pool) 
    {
        free(pool);
        pool = NULL;
    }

    return NULL;
}

//销毁线程池
int threadpool_destroy(ThreadPool* pool)
{
    if (pool == NULL)
        return -1;

    //关闭线程池
    pool->shut_down = 1;
    //阻塞回收管理者线程
    pthread_join(pool->manager_tids, NULL);
    //唤醒阻塞的消费者线程
    for (int i = 0; i < pool->live_num; ++i)
        pthread_cond_signal(&pool->cond_notempty);

    // 释放堆内存
    if (pool->task_queue)
    {
        free(pool->task_queue);
        pool->task_queue = NULL;
    }
    if (pool->workers_tids)
    {
        free(pool->workers_tids);
        pool->workers_tids = NULL;
    }

    pthread_mutex_destroy(&pool->mutexPool);
    pthread_mutex_destroy(&pool->mutexBusy);
    pthread_cond_destroy(&pool->notEmpty);
    pthread_cond_destroy(&pool->notFull);

    free(pool);
    pool = NULL;

    return 0;
}

//给线程池的任务队列里添加任务
void threadpool_addtask(ThreadPool* pool, void(*func)(void*), void* arg);

//获取线程池中工作的线程个数
int threadpool_busynum(ThreadPool* pool);

//获取线程池中活着的线程个数
int threadpool_alivenum(ThreadPool* pool);

//工作者线程（从任务队列里取任务并完成）
void* worker(void* arg);

//管理者线程（增删工作者线程）
void* manager(void* arg);

//线程池中的单个线程退出
void thread_exit(ThreadPool* pool);