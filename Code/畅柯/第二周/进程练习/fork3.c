#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
	pid_t pid;
	pid = fork();
	switch(pid){
		case 0 :
			while(1){
				printf("A background process ,PID :%d \n,ParentID :%s\n",getpid(),getpid());
				sleep(3);
			}
			break;
		case -1 :
			perror("Process creation failed\n");
			break;
		default :
			printf("I am parent process ,my pid is %d \n",getpid());
			exit(0);
	}
	return 0;
}
