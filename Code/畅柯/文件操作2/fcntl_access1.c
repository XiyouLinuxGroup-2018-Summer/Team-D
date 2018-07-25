#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
void my_err(const char * err_string,int line){
	fprintf(stderr,"line:%d",line);
	perror(err_string);
	exit(1);
}
int main(){
	int ret;
	int access_mode;
	int fd;

	if((fd=open("example2",O_CREAT|O_TRUNC|O_RDWR,S_IRWXU))==-1){
		my_err("open",__LINE__);
	}
	if((ret=fcntl(fd,F_SETFL,O_APPEND))==-1){
		my_err("fcntl",__LINE__);
	}

	//获取文件打开方式
	if((ret=fcntl(fd,F_GETFL,0))==-1){
		printf("fcntl",__LINE__);
	}
	
	access_mode=ret&O_ACCMODE;
	if(access_mode==O_RDONLY){
		printf("example access mode:read\n");
	}
	else if(access_mode==O_WRONLY){
		printf("example access mode:write\n");
	}
	else if(access_mode==O_RDWR){
		printf("example access mode:write and read\n");
	}
	if(ret&O_APPEND){
		printf(",append");
	}
	if(ret&O_NONBLOCK){
		printf(",nonblock");
	}
	if(ret&O_SYNC){
		printf(",sync");
	}
	printf("\n");
	return 0;
}
