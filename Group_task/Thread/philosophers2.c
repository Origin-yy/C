#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

pthread_mutex_t chopsticks[5];

void my_err(const char *err_string,int line,int errnumber);
void* philosopher(void *s);
int pick_two(int i);
void free_two(int i);

int main(void)
{
    int r;
    pthread_t tid[5];
    for(int i=0; i<5; i++)
    {
        r = pthread_mutex_init(&chopsticks[i],NULL);
        if(r != 0 )
            my_err()
    }

    for(int i=0; i<5; i++)
        pthread_create(&tid[i],NULL,philosopher,&i);

    for(int i=0; i<5; i++)
        pthread_join(tid[i],NULL);

    for(int i=0; i<5; i++)
        pthread_mutex_destroy(&chopsticks[i]);
    
    return 0;
}

//哲学家线程
void* philosopher(void *s)
{
    int *p = (int*)s;
    int i = *p;
    while(1)
    {
        //思考...
        if(pick_two(i))//饿了，尝试拿左右筷子
            free_two(i);       //成功拿起筷子，开始吃饭
        //思考...
    }
}
//编号为i的哲学家拿左右筷子
int  pick_two(int i) 
{
    int t = 0;
    pthread_mutex_lock(&chopsticks[i]);
    printf("哲学家%d拿起左筷子%d.\n",i,i);
    t = pthread_mutex_trylock(&chopsticks[(i+1)%5]);
    if(t != 0)
    {
        pthread_mutex_unlock(&chopsticks[i]);
        printf("哲学家%d无法拿起右筷子%d,所以放下左筷子.\n",i,(i+1)%5);
        return 0;
    }
    else
    {
        printf("哲学家%d拿起右筷子%d,开始吃饭\n",i,(i+1)%5);
        return 1;
    }
}
//编号为i的哲学家释放左右筷子
void free_two(int i)
{
    pthread_mutex_unlock(&chopsticks[i]);
    printf("哲学家%d放下左筷子%d.\n",i,i);
    pthread_mutex_unlock(&chopsticks[(i+1)%5]);
    printf("哲学家%d放下右筷子%d,开始思考.\n",i,(i+1)%5);
}
//
void errExitEN(const char *err_string,int line,int errnumber)
{
    fprintf(stderr,"line:%d %s %s\n",line, err_string, strerror(errnumber));
    exit(1);
}