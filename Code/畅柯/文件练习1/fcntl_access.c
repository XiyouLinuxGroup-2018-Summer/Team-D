#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
void my_err(const char * err_string,int line){
	fprintf(stderr,"line:%d",line);
	perror(err_string);
	exit(1);
}
int main(){
	int ret;
	int access_mode;
	int fd;
	if((fd=open("example_1",O_CREAT|O_TRUNC|O_RDWR,S_IRWXU))==-1){
		my_err("open",__LINE__);
	}
	//设置文件打开方式
	if((ret=fcntl(fd,F_SETFL,O_APPEND))<0){
		my_err("fcntl",__LINE__);
	}
	//获取文键打开方式
	if((ret=fcntl(fd,F_GETFL,0))==-1){
		my_err("fcntl",__LINE__);
	}
	access_mode=ret&O_ACCMODE;//将当前文件的打开方式和文件的打开方式的掩码作与运算
	if(access_mode==O_RDONLY){
		printf("example_64 access mode:read only\n");

	}else if(access_mode==O_WRONLY){
		printf("Example_64 access mode:write only!\n");
	}else if(access_mode==O_RDWR){
		printf("Example_64 access mode:write and read!\n");
	}
	if(ret & O_APPEND){
		printf(",append");
	}
	if(ret & O_NONBLOCK){
		printf(",nonblock");
	}
	if(ret & O_SYNC){
		printf(",sync");
	}
	printf("\n");
	return 0;
}
