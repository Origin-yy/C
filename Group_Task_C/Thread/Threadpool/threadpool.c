#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

// 任务结构体
typedef struct Task
{
    void (*function)(void* arg);
    void* arg;
}Task;

// 线程池结构体
typedef struct ThreadPool
{
    // 任务队列
    Task* task_queue;
    int queue_capacity;  // 容量
    int queue_size;      // 当前任务个数
    int queue_front;     // 队头 -> 取任务
    int queue_rear;      // 队尾 -> 放任务

    int min_num;             // 最小线程数
    int max_num;             // 最大线程数
    int busy_num;            // 工作中的线程的个数
    int live_num;            // 存活的线程的个数
    int exit_num;            // 要销毁的线程个数
    pthread_t manager_tid;    // 管理者线程ID
    pthread_t *workers_tids;   // 工作者线程ID
    pthread_mutex_t mutex_pool;  // 整个的线程池的互斥锁
    pthread_mutex_t mutex_busy;  // busy_num的互斥锁
    pthread_cond_t cond_notfull;     // 阻塞等待任务队列不满的条件变量
    pthread_cond_t cond_notempty;    // 阻塞等待任务队列不空的条件变量

    int shut_down;           // 是不是要销毁线程池, 销毁为1, 不销毁为0
}ThreadPool;

int NUMBER = 2;

// 错误函数
void my_err(const char *err_string, int line, int errnum);

// 创建线程池并初始化
ThreadPool *ThreadPoolCreat(int min, int max, int queue_size);

// 销毁线程池
int ThreadPoolDestroy(ThreadPool* pool);

// 给线程池添加任务
void ThreadPoolAdd(ThreadPool* pool, void(*func)(void*), void* arg);

// 获取线程池中工作的线程的个数
int GetBusynum(ThreadPool* pool);

// 获取线程池中活着的线程的个数
int GetAlivenum(ThreadPool* pool);

// 工作者线程
void* worker(void* arg);

// 管理者线程
void* manager(void* arg);

// 单个线程退出
void ThreadExit(ThreadPool* pool);


void my_err(const char *err_string, int line, int errnum)
{
    fprintf(stderr,"line:%d %s %s\n",line, err_string, strerror(errnum));
    exit(1);
}

ThreadPool* ThreadPoolCreat(int min, int max, int queue_size)
{
    ThreadPool* pool = (ThreadPool*)malloc(sizeof(ThreadPool));
    do 
    {
        if (pool == NULL)
        {
            printf("线程池申请堆内存失败\n");
            break;
        }

        pool->workers_tids = (pthread_t*)calloc(sizeof(pthread_t), max);
        if (pool->workers_tids == NULL)
        {
            printf("工作者线程ID数组申请堆内存失败\n");
            break;
        }

        pool->min_num = min;
        pool->max_num = max;
        pool->busy_num = 0;
        pool->live_num = min;    
        pool->exit_num = 0;

        if (pthread_mutex_init(&pool->mutex_pool, NULL) != 0 ||
            pthread_mutex_init(&pool->mutex_busy, NULL) != 0 ||
            pthread_cond_init(&pool->cond_notempty, NULL) != 0 ||
            pthread_cond_init(&pool->cond_notfull, NULL) != 0)
        {
            printf("互斥锁或条件变量申请堆内存失败\n");
            break;
        }

        // 任务队列
        pool->task_queue = (Task*)malloc(sizeof(Task) * queue_size);
        pool->queue_capacity = queue_size;
        pool->queue_size = 0;
        pool->queue_front = 0;
        pool->queue_rear = 0;

        pool->shut_down = 0;

        // 创建线程(初始创建min_num个数个线程)
        pthread_create(&pool->manager_tid, NULL, manager, pool);
        for (int i = 0; i < min; i++)
            pthread_create(&pool->workers_tids[i], NULL, worker, pool);

        return pool;
    } while (0);

    //do-while(0)循环只做一次，如果里面申请某个堆内存失败，就break出来，把申请成功的堆内存释放后返回NULL
    //如果申请堆内存成功的话就会返回一个线程池，不会执行下面的的free代码
    // 释放资源
    if (pool != NULL && pool->workers_tids != NULL) 
    {
        free(pool->workers_tids);
        pool->workers_tids = NULL;
    }

    if (pool != NULL && pool->task_queue != NULL)
    {
        free(pool->task_queue);
        pool->task_queue = NULL;
    }
    if (pool != NULL)
    {
        free(pool);
        pool = NULL;
    } 

    return NULL;
}

int ThreadPoolDestroy(ThreadPool* pool)
{
    if (pool == NULL)
    {
        return -1;
    }

    // 关闭线程池
    pool->shut_down = 1;
    // 阻塞回收管理者线程
    pthread_join(pool->manager_tid, NULL);
    // 唤醒阻塞的消费者线程
    for (int i = 0; i < pool->live_num; i++)
    {
        pthread_cond_signal(&pool->cond_notempty);
    }
    for (int i = 0; i < pool->max_num; i++)
        if (pool->workers_tids[i] != 0)
            pthread_join(pool->workers_tids[i],NULL);
    // 释放堆内存
    if (pool->task_queue)
    {
        free(pool->task_queue);
    }
    if (pool->workers_tids)
    {
        free(pool->workers_tids);
    }

    pthread_mutex_destroy(&pool->mutex_pool);
    pthread_mutex_destroy(&pool->mutex_busy);
    pthread_cond_destroy(&pool->cond_notempty);
    pthread_cond_destroy(&pool->cond_notfull);

    free(pool);
    pool = NULL;

    return 0;
}


void ThreadPoolAdd(ThreadPool* pool, void(*func)(void*), void* arg)
{
    pthread_mutex_lock(&pool->mutex_pool);
    while (pool->queue_size == pool->queue_capacity && !pool->shut_down)
    {
        // 阻塞生产者线程
        pthread_cond_wait(&pool->cond_notfull, &pool->mutex_pool);
    }
    if (pool->shut_down)
    {
        pthread_mutex_unlock(&pool->mutex_pool);
        return;
    }
    // 添加任务
    pool->task_queue[pool->queue_rear].function = func;
    pool->task_queue[pool->queue_rear].arg = arg;
    pool->queue_rear = (pool->queue_rear + 1) % pool->queue_capacity;
    pool->queue_size++;

    pthread_cond_signal(&pool->cond_notempty);
    pthread_mutex_unlock(&pool->mutex_pool);
}

int GetBusynum(ThreadPool* pool)
{
    pthread_mutex_lock(&pool->mutex_busy);
    int busy_num = pool->busy_num;
    pthread_mutex_unlock(&pool->mutex_busy);
    return busy_num;
}

int GetAlivenum(ThreadPool* pool)
{
    pthread_mutex_lock(&pool->mutex_pool);
    int alive_num = pool->live_num;
    pthread_mutex_unlock(&pool->mutex_pool);
    return alive_num;
}

void* worker(void* arg)
{
    ThreadPool* pool = (ThreadPool*)arg;

    while (1)
    {
        pthread_mutex_lock(&pool->mutex_pool);
        // 当前任务队列是否为空
        while (pool->queue_size == 0 && !pool->shut_down)
        {
            // 阻塞工作线程
            pthread_cond_wait(&pool->cond_notempty, &pool->mutex_pool);

            // 判断是不是要销毁线程
            if (pool->exit_num > 0)
            {
                pool->exit_num--;
                if (pool->live_num > pool->min_num)
                {
                    pool->live_num--;
                    pthread_mutex_unlock(&pool->mutex_pool);
                    ThreadExit(pool);
                }
            }
        }

        // 判断线程池是否被关闭了
        if (pool->shut_down)
        {
            pthread_mutex_unlock(&pool->mutex_pool);
            ThreadExit(pool);
        }

        // 从任务队列中取出一个任务
        Task task;
        task.function = pool->task_queue[pool->queue_front].function;
        task.arg = pool->task_queue[pool->queue_front].arg;
        // 移动头结点
        pool->queue_front = (pool->queue_front + 1) % pool->queue_capacity;
        pool->queue_size--;
        // 解锁
        pthread_cond_signal(&pool->cond_notfull);
        pthread_mutex_unlock(&pool->mutex_pool);

        printf("工作者线程：工作者线程 %ld 开始工作了\n", pthread_self());
        pthread_mutex_lock(&pool->mutex_busy);
        pool->busy_num++;
        pthread_mutex_unlock(&pool->mutex_busy);
        task.function(task.arg);

        printf("工作者线程：工作者线程 %ld 结束工作了\n", pthread_self());
        pthread_mutex_lock(&pool->mutex_busy);
        pool->busy_num--;
        pthread_mutex_unlock(&pool->mutex_busy);
    }
    return NULL;
}

void* manager(void* arg)
{
    ThreadPool* pool = (ThreadPool*)arg;
    while (!pool->shut_down)
    {
        // 每隔3s检测一次
        sleep(3);

        // 取出线程池中任务的数量和当前线程的数量
        pthread_mutex_lock(&pool->mutex_pool);
        int queue_size = pool->queue_size;
        int live_num = pool->live_num;
        pthread_mutex_unlock(&pool->mutex_pool);

        // 取出忙的线程的数量
        pthread_mutex_lock(&pool->mutex_busy);
        int busy_num = pool->busy_num;
        pthread_mutex_unlock(&pool->mutex_busy);

        // 添加线程
        // 任务的个数>存活的线程个数 && 存活的线程数<最大线程数
        if (queue_size > live_num && live_num < pool->max_num)
        {
            pthread_mutex_lock(&pool->mutex_pool);
            int counter = 0;
            for (int i = 0; i < pool->max_num && counter < NUMBER
                && pool->live_num < pool->max_num; ++i)
            {
                if (pool->workers_tids[i] == 0)
                {
                    pthread_create(&pool->workers_tids[i], NULL, worker, pool);
                    counter++;
                    pool->live_num++;
                }
            }
            pthread_mutex_unlock(&pool->mutex_pool);
        }
        // 销毁线程
        // 忙的线程*2 < 存活的线程数 && 存活的线程>最小线程数
        if (busy_num * 2 < live_num && live_num > pool->min_num)
        {
            pthread_mutex_lock(&pool->mutex_pool);
            pool->exit_num = NUMBER;
            pthread_mutex_unlock(&pool->mutex_pool);
            // 让工作的线程自杀
            for (int i = 0; i < NUMBER; ++i)
            {
                pthread_cond_signal(&pool->cond_notempty);
            }
        }
    }
    return NULL;
}

void ThreadExit(ThreadPool* pool)
{
    pthread_t tid = pthread_self();
    for (int i = 0; i < pool->max_num; ++i)
    {
        if (pool->workers_tids[i] == tid)
        {
            pool->workers_tids[i] = 0;
            printf("线程退出函数：工作者线程 %ld 退出了\n", tid);
            break;
        }
    }
    pthread_exit(NULL);
}

void taskFunc(void* arg)
{
    long int num = (long)arg;
    printf("单任务函数：工作者线程 %ld 正在进行任务 %ld\n",
        pthread_self(), num);
    sleep(1);
}

int main()
{
    int r = 0;    //标记调用是否成功返回
    // 创建线程池
    ThreadPool* pool = ThreadPoolCreat(3, 10, 100);
    if (pool == NULL)
        fprintf(stderr, "ThreadPool 失败.\n");

    for (int i = 0; i < 100; ++i)
    {
        long int num = i;
        ThreadPoolAdd(pool, taskFunc, (void*)num);
        printf("主函数：任务 %ld 被添加到任务队列当中了.\n",num);
    }

    sleep(30);

    r = ThreadPoolDestroy(pool);
    if (r != 0)
        fprintf(stderr, "ThreadPoolDestroy 失败.\n");

    return 0;
}
