#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
pthread_once_t once = PTHREAD_ONCE_INIT;

void run(void)
{
        printf("Founction run is running in thread %lu\n",pthread_self());
}

void * thread1(void *arg)
{
        pthread_t thid=pthread_self();
        printf("当前的线程 ID 是 %lu\n",thid);
        pthread_once(&once,run);
        printf("thread1 结束\n");
}

void * thread2(void * arg)
{
        pthread_t thid=pthread_self();
        printf("当前的线程 ID 是 %lu\n",thid);
        pthread_once(&once,run);
        printf("thread2 结束\n");
}

int main()
{
        pthread_t thid1,thid2;

        pthread_create(&thid1,NULL,thread1,NULL);
        pthread_create(&thid2,NULL,thread2,NULL);
        sleep(3);
        printf("主线程退出!\n");
        exit(0);
}
