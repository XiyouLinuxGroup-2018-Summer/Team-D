#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
int main(int argc , char* argv[] , char ** environ){
	pid_t pid ;
	int stat_val ;
	printf("Exec example !\n");
	pid = fork();
	switch(pid){
		case -1 :
			perror("process create faled!\n");
			exit(1) ;
		case 0 :
			
			printf("Child process is running\n");
			printf("my pid = %d ,parentpid = %d\n",getpid(),getppid());
			printf("uid = %d ,gid = %d \n",getuid(),getgid());
			execve("processimage", argv , environ);
			printf("process never go to here!\n");
			exit(0);
		default :
			printf("Parent process is running \n");
			break;
	}
	wait(&stat_val);
	exit(0);
}
