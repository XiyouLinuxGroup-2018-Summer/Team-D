#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <pthread.h>
#include <unistd.h>
#include<errno.h>
#include<fcntl.h>

int fd;
int fp;
int t=0;
pthread_mutex_t mutex;
pthread_cond_t cond;
void my_err(const char * err_string,int line)
{
    fprintf(stderr,"line:%d ",line);
    perror(err_string);
    exit(1);
}
void * thread1(void *arg)
{
    while(1)
    {
        struct stat buff;
        pthread_mutex_lock(&mutex);
        char buf[10]="0123456789";
        pthread_cond_wait(&cond,&mutex);
        if((fd=open("myfile",O_WRONLY|O_CREAT|O_APPEND))==-1)
            my_err("open",__LINE__);
        if(lstat("myfile",&buff)==-1)
            my_err("lstat",__LINE__);
        t=buff.st_size;
        if(t<100)
        {
            if(write(fd,buf,strlen(buf))!=strlen(buf))
            {
                my_err("write",__LINE__);
            }
        }
        close(fd);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
}
void * thread2(void *arg)
{
    while(1)
    {
        struct stat buf;
        char buff[100];
        pthread_mutex_lock(&mutex);
        char src[7];
        if((fd=open("myfile",O_RDONLY))==-1)
            my_err("open",__LINE__);
        if(lstat("myfile",&buf)==-1)
            my_err("lstat",__LINE__);
        t=buf.st_size;
        if(t>0)
        {
            int k;
            read(fd,src,6);          //每次读出6个字节
            src[7]='\0';
            printf("%s\n",src);
            /*删除已经读出的数据*/
            for(int i=0;i<t;i++)
            {
                read(fd,buff,t-6);
            }
            close(fd);
            if((fp=open("myfile",O_WRONLY|O_CREAT|O_TRUNC,S_IRWXU))==-1)
                my_err("open",__LINE__);
            if(write(fp,buff,t-6)!=t-6)
                my_err("write",__LINE__);
            close(fp);
        }
        close(fd);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
}
int main()
{
    pthread_t tid1,tid2;
    pthread_mutex_init(&mutex,NULL);
    pthread_cond_init(&cond,NULL);
    pthread_create(&tid1,NULL,(void *)thread1,NULL);
    pthread_create(&tid2,NULL,(void *)thread2,NULL);
    if((fd=creat("myfile",S_IRWXU))==-1)
    {
        my_err("creat",__LINE__);
    }
    do
    {
        pthread_cond_signal(&cond);
    }while(1);
}
