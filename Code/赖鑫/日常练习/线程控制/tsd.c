#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>
pthread_key_t key;
void * thread2(void *arg)
{
  int tsd =5;
  printf("线程２ %d 正在运行\n",pthread_self());
  pthread_setspecific(key,(void *)tsd);       //为线程２分配键值５
  printf("线程２ %d 的键值为：%d\n",pthread_self(),pthread_getspecific(key));
}
void * thread1(void *arg)
{
  int tsd=0;
  pthread_t thid2;
  printf("线程1 %d 正在运行\n",pthread_self());
  pthread_setspecific(key,(void *)tsd);      //为线程１分配键值
  pthread_create(&thid2,NULL,thread2,NULL);  //创建线程２．运行函数
  sleep(4);
  printf("线程1 %d 的键值为：%d\n",pthread_self(),pthread_getspecific(key));
}
int main()
{
  pthread_t thid1;
  printf("主线程正在运行：\n");
  pthread_key_create (&key,NULL);      //创建键
  pthread_create (&thid1,NULL,thread1,NULL);     //创建新线程
  sleep(8);
  pthread_key_delete(key);
  printf("主进程结束\n");
  return 0;

}
//要注意主线程和线程１之间的休眠sleep()关系，如果主线程的休眠时间结束，那么直接回到主线程
