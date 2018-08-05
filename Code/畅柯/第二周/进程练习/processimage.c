#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
int main(int argc , char** argv ){

	int i;

	printf("I'm a process image !\n");
	printf("My pid =%d ,parentpid = %d\n",getpid(),getppid());
	printf("uid : %d ,gid = %d\n",getuid(),getgid());

	for(i=0 ; i < argc ;i++)
		printf("argv[%d] : %s\n",i,argv[i]);
}
