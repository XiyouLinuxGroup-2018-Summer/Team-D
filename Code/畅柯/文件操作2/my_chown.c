#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<time.h>
#include<errno.h>
int main(int argc,char** argv){
	struct stat buf;
	//检验参数的合法性
	if(argc!=4){
		perror("error usage:");
		exit(0);
	}
	if(stat(argv[1],&buf)==-1){
		perror("stat:");
		exit(1);
	}
}
