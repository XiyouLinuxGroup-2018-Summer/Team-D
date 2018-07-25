#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<errno.h>
int main(int argc,char **argv){
	struct stat buf;
	//检查参数个数
	if(argc!=2){
		printf("Usages:my_stat <filename>\n");
		exit(0);
	}
	//获取文件属性
	if(stat(argv[1],&buf)==-1){
		perror("stat:");
		exit(1);
	}
	
	//打印文件属性
	printf("device is:%d\n",buf.st_dev);
	printf("time of last access is:%s\n",ctime(&buf.st_atime));
	return 0;

}
