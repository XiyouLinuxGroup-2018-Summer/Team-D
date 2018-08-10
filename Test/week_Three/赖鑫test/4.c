#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<fcntl.h>
pthread_mutex_t number_mutex;
int s=0;

void * thread1(void *arg)
{
  pthread_mutex_lock (&number_mutex);
  if(s<=90)
  {
    int fd;
    if(fd=open("filename3",O_RDWR|O_CREAT|O_APPEND,0777)==-1)
    {
      perror("open1");
      exit(1);
    }
    char write_buf[10]={"123456789"};
    write(fd,write_buf,9);
    s=s+9;
    close(fd);
  }
  pthread_mutex_unlock(&number_mutex);
}

void * thread2(void *arg)
{
  pthread_mutex_lock (&number_mutex);
  if(s!=0)
  {
    int fd;
    if(fd=open("filename3",O_RDONLY)==-1)
    {
      perror("open2");
      exit(1);
    }
    char buf[100]={'\0'};
    read(fd,buf,s);
    printf("%s\n",buf);
    close(fd);
    if((fd=open("filename3",O_TRUNC|O_RDWR))==-1)
    {
      perror("open3");
      exit(1);
    }
    s=0;
    close(fd);
  }
  pthread_mutex_unlock(&number_mutex);
}

int main()
{
  pthread_t thid1,thid2;
  while(1)
  {
    pthread_create(&thid1,NULL,thread1,NULL);
    pthread_create(&thid2,NULL,thread2,NULL);
  }

}
