#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
int main(int argc ,char * argv[] ,char ** environ){
	int i ;
	
	printf("hello world!I'm a image process!\n");
	printf("pid = %d ,parentpid =  %d\n ",getpid(),getppid());
	printf("uid = %d gid = %d\n",getuid ,getgid());

	for(i = 0 ; i< argc ;i++){
		printf("argv[%d]:%s\n" , i ,argv[i]);
	}
}

