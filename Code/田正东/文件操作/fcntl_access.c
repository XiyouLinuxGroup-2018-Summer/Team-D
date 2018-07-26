#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
void error(const char * err_string,int line)
{
    fprintf(stderr,"line:%d",line);
	perror(err_string);
	exit(1);
}
int main()
{
    int ret;
	int access_mode;
	int fd;
	if((fd=open("test2",O_CREAT|O_TRUNC|O_RDWR,S_IRWXU))==-1){
	    error("open",__LINE__);
	}
	if((ret=fcntl(fd,F_SETFL,O_APPEND))<0){
	    error("fcntl",__LINE__);
	}
	if((ret=fcntl(fd,F_GETFL,0))<0){
	    error("fcntl",__LINE__);
	}
	access_mode=ret&O_ACCMODE;
	if(access_mode==O_RDONLY){
	    printf("test2 access mode:read only");
	}
	else if(access_mode==O_WRONLY){
	    printf("test2 access mode:write only");
	}
	else if(access_mode==O_RDWR){
	    printf("test2 access mode:read + write");
	}
	if(ret&O_APPEND){
	    printf(" ,append");
	}
	if(ret&O_NONBLOCK){
	    printf(" ,nonblock");
	}
	if(ret&O_SYNC){
	    printf(",sync");
	}
	printf("\n");
	return 0;
}
