#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
pthread_once_t once = PTHREAD_ONCE_INIT;
void run(void)
{
  printf("程序正在运行，线程ＩＤ： %u \n",pthread_self());
}
void * thread1(void *arg)
{
  pthread_t thid = pthread_self();           //thid获取函数，为当前进程ＩＤ
  printf("当前线程的ＩＤ为：%u\n",thid);         //输出当前线程ＩＤ
  pthread_once(&once,run);                  //保证线程函数run()函数只运行一次
  printf("线程１结束\n");
}
void * thread2(void *arg)
{
  pthread_t thid = pthread_self();
  printf("当前线程的ＩＤ为：%u\n",thid);      //第二个线程ＩＤ
  pthread_once(&once,run);                 //因为在第一个函数中已经使用函数对run函数在该线程中只执行一次，所以就算这个函数也使用了run函数，但是并没有执行
  printf("线程２结束\n");
}
int main()
{
  pthread_t thid1,thid2;
  pthread_create(&thid1,NULL,thread1,NULL);
  pthread_create(&thid2,NULL,thread2,NULL);
  sleep(3);
  printf("主线程退出\n");
  exit(0);
}
