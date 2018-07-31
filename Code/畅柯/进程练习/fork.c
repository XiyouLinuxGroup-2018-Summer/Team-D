#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
int main()
{
	pid_t pid ;
	printf("进程学习!\n");
	pid = fork();
	switch(pid) 
	{
		case 0 :
			printf("Child process is running ,Curpid = %d ,ParentPid is %d\n", pid , getpid());
		break ;
		case -1 :
			perror("Process creation failed !\n");
			break ;
		default : 
			printf("Parent process is running , ChildPid is %d ,ParentPid is %d \n",pid ,getpid());
			break ;
	}
	exit(0) ;
}
