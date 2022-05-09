/*
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

sem_t chopsticks[5];

void* philosopher(void *s);
void pick_two(int i);
void free_two(int i);

int main(void)
{
    for(int i=0; i<5;i++)
        sem_init(&chopsticks[i],0,1);

    int philosophers[5] = {0,1,2,3,4};
    pthread_t tid[5];

    for(int i=0; i<5; i++)
        pthread_create(&tid[i],NULL,philosopher,&philosophers[i]);
    for(int i=0;i<5; i++)
        sem_destroy(&chopsticks[i]);
    for(int i=0; i<5; i++)
        pthread_join(tid[i],NULL);
    return 0;
}
//哲学家线程
void* philosopher(void*s)
{
    int *p = (int*)s;
    int i = *p;
    while(1)
    {
        //思考
        pick_two(i);       //饿了，拿左右筷子
        //吃饭
        free_two(i);       //吃完，放左右筷子
    }
}
//编号为i的哲学家拿左右筷子
void pick_two(int i) 
{
    if(i%2 == 1) //如果是奇数号哲学家，先左后右
    {
        sem_wait(&chopsticks[i]);
        printf("哲学家%d拿起左筷子%d.\n",i,i);
        sem_wait(&chopsticks[(i+1)%5]);
        printf("哲学家%d拿起右筷子%d,开始吃饭.\n",i,(i+1)%5);
    }
    else   //如果是偶数号哲学家，先右后左
    {
        sem_wait(&chopsticks[(i+1)%5]);
        printf("哲学家%d拿起右筷子%d.\n",i,(i+1)%5);
        sem_wait(&chopsticks[i]);
        printf("哲学家%d拿起左筷子%d,开始吃饭.\n",i,i);
    }
}
//编号为i的哲学家释放左右筷子
void free_two(int i)
{
    if(i%2 == 1) //如果是奇数号哲学家，先左后右
    {
        sem_post(&chopsticks[i]);
        printf("哲学家%d放下左筷子%d.\n",i,i);
        sem_post(&chopsticks[(i+1)%5]);
        printf("哲学家%d放下右筷子%d,开始思考.\n",i,(i+1)%5);
    }
    else   //如果是偶数号哲学家，先右后左
    {
        sem_post(&chopsticks[(i+1)%5]);
        printf("哲学家%d放下右筷子%d.\n",i,(i+1)%5);
        sem_post(&chopsticks[i]);
        printf("哲学家%d放下左筷子%d,开始思考.\n",i,i);
    }
}
