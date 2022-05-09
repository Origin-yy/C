#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

int main(void)
{
    pthread_t tid[5];
    pthread_mutex_t *chopsticks[5] = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) * 5);
    for(int i=0; i<5; i++)
        pthread_mmutex_init
    for(int i=0; i<5; i++)
        pthread_create(&tid[i],NULL,philosopher,&philosophers[i]);
    for(int i=0;i<5; i++)
        sem_destroy(&chopsticks[i]);
    for(int i=0; i<5; i++)
        pthread_join(tid[i],NULL);
    return 0;
}