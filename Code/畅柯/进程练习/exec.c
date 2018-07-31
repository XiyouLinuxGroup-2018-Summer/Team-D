#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
int main(int argc ,char * argv[], char** environ){
	
	pid_t pid;
	int stat_val;

	printf("exec test");
	pid = fork();
	switch(pid){
		case 0 :
			printf("Child process is running!child id = %d,parentpid = %d\n",getpid(),getppid());
			printf("uid = %d ,gid = %d\n",getuid(),getgid());
			execve("image",argv,environ) ;
			printf("this place never been discover!\n");
			exit(0);
		case -1 :
			printf("Process creation failed!\n");
			break;
		default :
			printf("Parent is running\n");
			break;
	}
	wait(&stat_val);


}
