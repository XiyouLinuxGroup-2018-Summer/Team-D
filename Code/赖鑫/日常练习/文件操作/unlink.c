#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
void err1(const char *s,int line)
{
    fprintf(stderr,"line:%d",line);
    perror(s);
    exit(1);
}
int main()
{
    int fd;
    char buf[32];
    if((fd=open("temp",O_RDWR|O_CREAT|O_TRUNC,S_IRWXU))<0)
        err1("open",__LINE__);
    if(unlink("temp")<0)
        err1("unlink",__LINE__);
    printf("文件未连接\n");
    if(write(fd,"temp",5)<0)
        err1("write",__LINE__);
    if((lseek(fd,0,SEEK_SET))==-1)
        err1("lseek",__LINE__);
    if(read(fd,buf,5)<0)
        err1("read",__LINE__);
    printf("%s\n",buf);

}
