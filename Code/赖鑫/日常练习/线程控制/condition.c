#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

pthread_mutex_t mutex;
pthread_cond_t cond;

void *thread1(void *arg)
{
  pthread_cleanup_push(pthread_mutex_unlock,&mutex);       //－－－自动释放资源函数
  while(1)
  {
    printf("线程１正在运行\n");
    pthread_mutex_lock(&mutex);      //设置线程１互斥锁
    pthread_cond_wait(&cond,&mutex);     //
    printf("线程应用条件：\n");
    pthread_mutex_unlock(&mutex);    //解锁
    sleep(4);
  }
  pthread_cleanup_pop(0);
}
void *thread2(void *arg)
{
  while(1)
  {
    printf("线程２正在运行\n");
    pthread_mutex_lock(&mutex);       //设置线程２互斥锁
    pthread_cond_wait(&cond,&mutex);   //
    printf("线程２应用条件:\n");
    pthread_mutex_unlock(&mutex);
    sleep(1);
  }
}
int main()
{
  pthread_t tid1,tid2;
  printf("条件变量学习\n");
  pthread_mutex_init(&mutex,NULL);      //初始化一个互斥锁
  pthread_cond_init(&cond,NULL);       //初始化一个条件变量
  pthread_create(&tid1,NULL,(void *)thread1,NULL);     //创建新的线程１
  pthread_create(&tid2,NULL,(void *)thread2,NULL);     //创建新的线程2
  do {
    pthread_cond_signal(&cond);
  } while(1);
  sleep(50);
  pthread_exit(0);
}
