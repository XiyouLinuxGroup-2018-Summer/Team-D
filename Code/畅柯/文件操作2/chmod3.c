#include<stdlib.h>
#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<errno.h>
int main(int argc , char ** argv){
	struct stat buf;
	//检查参数是否合法
	if(argc!=2){
		printf("\n命令不存在,请重新输入!\n");
		exit(0);
	}
	//获取文件属性
	if(stat(argv[1],&buf)==-1){
		perror("stat:");
		exit(1);
	}
	


}
