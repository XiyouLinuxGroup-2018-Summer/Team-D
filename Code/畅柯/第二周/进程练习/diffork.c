#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
int globVar=5;
int main()
{
	pid_t pid;
	int var=1 , i;
	printf("fork 和 vfork 的不同!\n");
//	pid = fork();
	pid = vfork();
	switch(pid)
	{
		case 0 :
			i = 3;
			while(i-- > 0){
				printf("Child process is running !\n");
				globVar++;
				var++;
				sleep(1);
			}
			printf("Child's globVar = %d ,var =%d \n",globVar,var);
			exit(1);
		
		case -1 :
			printf("Process creation failed !\n");
			break;
		
		default :
			i = 5;
			printf("\n*************************\n");
			while(i-- > 0)
			{
				printf("Parent process is running \n");
				globVar++;
				var++;
				sleep(1);
			}
			printf("Parent's globVar = %d , var = %d\n",globVar , var);
			printf("\n******************************\n");
			break ;
	}
	printf("Parent's globVar = %d , var =%d \n",globVar, var);

	exit(0);
}
