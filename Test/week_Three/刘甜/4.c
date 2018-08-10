#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<ctype.h>
#include<pthread.h>

#define MAX_THREAD 3 //线程个数

unsigned long long main_counter, counter[MAX_THREAD];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void* thread_worker(void* arg);

int main()
{
    int i, rtn, ch;
    int tmp[MAX_THREAD];
    pthread_t pthread_id[MAX_THREAD] = { 0 }; // 存放线程id
    for (i = 0;i<MAX_THREAD;i++)
    {
       pthread_create(&pthread_id[i],NULL,(void*)thread_worker,(void *)&i); 
    }
    do //用户按一次回车执行下面的循环体一次,按q退出
    {
        unsigned long long sum = 0;
         //求所有线程的 counter 的和
        for (i = 0; i < MAX_THREAD; i++)
        {
            sum += counter[i];
            printf("%llu ", counter[i]);
        }
        printf("%llu/%llu", main_counter, sum);
     }while ((ch = getchar()) != 'q');
   
    return 0;
}
void* thread_worker(void* arg)
{
    int thread_num;
    thread_num=*((int *)arg);
    for (;;)
    {
       counter[thread_num]++;
       main_counter++;
    }
}

//A、我认为相等
//B、大于
//C、程序最后的执行结果，只有counter[0]和main_counter值增加了，即只有主线程和线程id为pthread_id[0]的线程在运行。
//D、我觉得它是被主线程强制退出的，每一次回车和回车之间时间越长，counter[0]和main_counter的增值越大。
