#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
int main()
{
    int fd;
    if((fd=open("aaadfaf4.c",O_CREAT|O_EXCL))==-1)
    {//if((fd=creat("aaadfaf4.c",S_IRWWXU))==-1)
        perror("open");
        exit(1);
    }
    else
        printf("创建新文件成功！\n");
    close(fd);
}
