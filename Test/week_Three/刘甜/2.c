#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

pthread_mutex_t mutex;
pthread_cond_t cond1;
pthread_cond_t cond2;
pthread_cond_t cond3;
void * thread1(void *arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond1,&mutex);
        printf("A\n");
        pthread_cond_signal(&cond2);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
}
void * thread2(void *arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond2,&mutex);
        printf("B\n");
        pthread_cond_signal(&cond3);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
}
void * thread3(void *arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond3,&mutex);
        printf("C\n");
        //pthread_cond_signal(&cond1);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
}

int main(void)
{
    int n=9;
    pthread_t tid1,tid2,tid3;
    pthread_mutex_init(&mutex,NULL);
    pthread_cond_init(&cond1,NULL);
    pthread_cond_init(&cond2, NULL) ;
    pthread_cond_init(&cond3, NULL);
    pthread_create(&tid1,NULL,(void *)thread1,NULL);
    pthread_create(&tid2,NULL,(void *)thread2,NULL);
    pthread_create(&tid3,NULL,(void *)thread3,NULL);
    sleep(2);
    do{
        pthread_cond_signal(&cond1);
        sleep(3);
    }while(1);
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    pthread_join(tid3,NULL);
    sleep(50);
    pthread_exit(0);
}
