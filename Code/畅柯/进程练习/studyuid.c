#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<errno.h>
int main(){
	int fd ;

	printf("用户ID学习:\n");
	printf("Process's uid = %d ,euid =%d \n",getuid(),geteuid());//显示用户的实际id和有效id
	if((fd = open("test.c" ,O_RDWR))==-1){
		printf("Open failure, errno id %d  :%s ",errno ,strerror(errno));
		exit(1);
	}
	else{
		printf("Open successfully!\n");
	}
	close(fd);
	exit(0);
}
