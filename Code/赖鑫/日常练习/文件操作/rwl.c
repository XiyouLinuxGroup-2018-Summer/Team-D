#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
void my(char * error,int line)
{
    fprintf(stderr,"line:%d",line);
    perror(error);
    exit(1);
}

int readd(int fd)
{
    int len,rec,i;
    char r[64];
    if((len=lseek(fd,0,SEEK_END))==-1)
        my("lseek",__LINE__);
    if((lseek(fd,0,SEEK_SET))==-1)
        my("lseek",__LINE__);
    printf("长度：%d",len);
    if(read(fd,r,len)==-1)
        my("read",__LINE__);
    for(i=0;i<len;i++)
    {
        printf("%c",r[i]);
    }
    printf("\n");
    return 0;
}
int main()
{
    char s[32]="Hello World!";
    int fd;
    if((fd=open("examplr 655.c",O_CREAT|O_TRUNC|O_RDWR,S_IRWXU))==-1)
        my("open",__LINE__);
    else
        printf("文件建立成功!\n");
    if((write(fd,s,strlen(s))!=strlen(s)))
        my("write",__LINE__);
    readd(fd);
   if( lseek(fd,10,SEEK_END)==-1)
       my("lseek",__LINE__);
	if((write(fd,s,strlen(s))!=strlen(s)))
        my("write",__LINE__);
   readd(fd);
   close(fd);

}
