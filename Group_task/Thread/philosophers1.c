/*
信号量
奇数号哲学家，先左后右.
偶数号哲学家，先右后左
*/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

sem_t chopsticks[5];

void* philosopher(void *s);
void pick_two(int i);
void free_two(int i);
void my_error(const char *err_string,int line,int errnumber);

int main(void)
{
    int r = 0;

    for(int i=0; i<5;i++)
    {
        r = sem_init(&chopsticks[i],0,1);
        if(r != 0)
            my_error("sem_init",__LINE__,r);
    }
    int philosophers[5] = {0,1,2,3,4};
    pthread_t tid[5];

    for(int i=0; i<5; i++)
    {
        r = pthread_create(&tid[i],NULL,philosopher,&philosophers[i]);
        if(r != 0)
            my_error("pthread_create",__LINE__,r);
    }
    for(int i=0;i<5; i++)
    {
        r = sem_destroy(&chopsticks[i]);
        if(r != 0)
            my_error("sem_destroy",__LINE__,r);
    }
    for(int i=0; i<5; i++)
    {
        pthread_join(tid[i],NULL);
        if(r != 0)
            my_error("pthread_join",__LINE__,r);
    }
    return 0;
}
//哲学家线程
void* philosopher(void*s)
{
    int *p = (int*)s;
    int i = *p;
    while(1)
    {
        //思考...
        pick_two(i);       //饿了，拿左右筷子
        //吃饭...
        free_two(i);       //吃完，放左右筷子
    }
}
//编号为i的哲学家拿左右筷子
void pick_two(int i) 
{
    int r = 0;
    if(i%2 == 1) //如果是奇数号哲学家，先左后右
    {
        r = sem_wait(&chopsticks[i]);
        if(r != 0)
            my_error("sem_wait",__LINE__,r);
        printf("哲学家%d拿起左筷子%d.\n",i,i);
        sem_wait(&chopsticks[(i+1)%5]);
        if(r != 0)
            my_error("sem_wait",__LINE__,r);
        printf("哲学家%d拿起右筷子%d,开始吃饭.\n",i,(i+1)%5);
    }
    else   //如果是偶数号哲学家，先右后左
    {
        r = sem_wait(&chopsticks[(i+1)%5]);
        if(r != 0)
            my_error("sem_wait",__LINE__,r);
        printf("哲学家%d拿起右筷子%d.\n",i,(i+1)%5);
        r = sem_wait(&chopsticks[i]);
        if(r != 0)
            my_error("sem_wait",__LINE__,r);
        printf("哲学家%d拿起左筷子%d,开始吃饭.\n",i,i);
    }
}
//编号为i的哲学家释放左右筷子
void free_two(int i)
{
    int r = 0;
    if(i%2 == 1) //如果是奇数号哲学家，先左后右
    {
        r = sem_post(&chopsticks[i]);
        if(r != 0)
            my_error("sem_post",__LINE__,r);
        printf("哲学家%d放下左筷子%d.\n",i,i);
        r = sem_post(&chopsticks[(i+1)%5]);
        if(r != 0)
            my_error("sem_post",__LINE__,r);
        printf("哲学家%d放下右筷子%d,开始思考.\n",i,(i+1)%5);
    }
    else   //如果是偶数号哲学家，先右后左
    {
        r = sem_post(&chopsticks[(i+1)%5]);
        if(r != 0)
            my_error("sem_post",__LINE__,r);
        printf("哲学家%d放下右筷子%d.\n",i,(i+1)%5);
        r = sem_post(&chopsticks[i]);
        if(r != 0)
            my_error("sem_post",__LINE__,r);
        printf("哲学家%d放下左筷子%d,开始思考.\n",i,i);
    }
}
//函數
void my_error(const char *err_string,int line,int errnumber)
{
    fprintf(stderr,"line:%d %s %s\n",line, err_string, strerror(errnumber));
    exit(1);
}