#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
pthread_mutex_t number_mutex;
char s='A';
void * thread1(void *arg)
{

  pthread_mutex_lock (&number_mutex);
  if(s=='A')
  {//pthread_t thid=pthread_self();
    printf("A");
    s='B';
  }
  pthread_mutex_unlock(&number_mutex);
}
void * thread2(void *arg)
{
  pthread_mutex_lock (&number_mutex);
  if(s=='B')
  {//pthread_t thid=pthread_self();
    printf("B");
    s='C';
  }
  pthread_mutex_unlock(&number_mutex);
}
void * thread3(void *arg)
{
  pthread_mutex_lock (&number_mutex);
  if(s=='C')
  {//pthread_t thid=pthread_self();
    printf("C");
    s='A';
  }
  pthread_mutex_unlock(&number_mutex);
}
int main()
{
  pthread_t thid1,thid2,thid3;
  while(1)
  {
    pthread_create(&thid1,NULL,thread1,NULL);
    pthread_create(&thid2,NULL,thread2,NULL);
    pthread_create(&thid3,NULL,thread3,NULL);
  }

}
