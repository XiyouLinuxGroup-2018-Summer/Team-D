#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
int thread(void *arg)
{
  pthread_t newthid;
  newthid = pthread_self();
  printf("这是一个新的进程，进程ＩＤ为：%u\n",newthid);
  return 0;
}
int main()
{
  pthread_t thid;
  printf("主进程，进程ＩＤ为：%u \n",pthread_self() );
  if(pthread_create(&thid,NULL,(void *)thread,NULL)!=0)
  {
    printf("创建进程失败\n");
    exit(1);
  }
  sleep(1);
  exit(0);
}
