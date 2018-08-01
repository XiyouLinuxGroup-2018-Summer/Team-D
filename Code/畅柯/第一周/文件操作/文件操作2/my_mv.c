#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<errno.h>
int main(int argc,char ** argv){
	//检查参数的合法性
	if(argc!=3){
		printf("my_mv <old_file><new_file>\n");
		exit(0);
	}
	if(rename(argv[1],argv[2])<0){
		perror("rename");
		exit(1);
	}
	return 0;
}
