#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#define N 30
void my_err(char * err_string ,int line){
	fprintf(stderr,"line:%d",line);
	perror(err_string);
}
int main(int argc,char** argv){
	char buf[N];
	if(getcwd(buf,N)==NULL){
		my_err("getcwd",__LINE__);
		exit(1);
	}
	printf("%s\n",buf);
	return 0;
}
