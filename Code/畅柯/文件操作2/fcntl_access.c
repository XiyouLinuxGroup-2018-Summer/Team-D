#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>
void my_err(const char* str,int line){
	fprintf(stderr,"line:%d",line);
	perror(str);
	exit(1);

}
int main(){
	int ret;
	int access_mode;
	int fd;
	if(fd=open("example",O_CREAT|O_TRUNC|O_RDWR,S_IRWXU)==-1){
		my_err("open",__LINE__);
	}
	//获取文件打开方式
	if((ret=fcntl(fd,F_GETFL,0))<0){
		my_err("fcntl",__LINE__);
	}
	access_mode=ret&O_ACCMODE ;
	if(access_mode==O_RDONLY){
		printf("Example access mode:read only!\n");
	}
	else if(access_mode==O_WRONLY){
		printf("Example access mode:write only!\n");
	}
	else if(access_mode==O_RDWR){
		printf("Example access mode:read and write!\n");
	}
	if(ret&O_APPEND){
		printf(" ,append");
	}
	if(ret&O_NONBLOCK){
		printf(",NONBLOCK\n");
	}
	if(ret&O_SYNC){
		printf(",sync\n");
	}	
	printf("\n");
	return 0;
}
