#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
int count = 0;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* pthread_run()
{
    int i = 0;
    int ret = 0;
    while(i < 5000)
    {
	pthread_mutex_lock(&lock);
        i++;
        ret = count;
        printf("process ID:%d,pthread ID:%lu,count:%d\n",getpid(),pthread_self(),count);
        count = ret + 1;
	pthread_mutex_lock(&lock);
    }
}
 
int main()
{
    int ret = 0;
    pthread_t id1;
    pthread_t id2;
    pthread_create(&id1,NULL,&pthread_run,NULL);
    pthread_create(&id2,NULL,&pthread_run,NULL);
    pthread_join(id1,NULL);  //wait
    pthread_join(id2,NULL);
    printf("count: %d\n",count);
    return 0;
}

