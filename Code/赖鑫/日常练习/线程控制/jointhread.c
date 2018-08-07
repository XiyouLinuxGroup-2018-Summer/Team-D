#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
void assi(void *arg)
{
  printf("我在帮忙做一些工作\n");
  sleep(3);
  pthread_exit(0);
}
int main(void)
{
  pthread_t ass;
  int status;
  pthread_create(&ass,NULL,(void *)assi,NULL);
  pthread_join(ass,(void *)&status);         //使用pthread_join()函数，主线程等待assi线程结束再进行
  printf("函数结束退出码：%d\n",&status);
  return 0;
}
