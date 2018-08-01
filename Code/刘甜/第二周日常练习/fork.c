#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

int main(void)
{
    pid_t pid;
    printf("process Creation Study\n");
    pid = fork();
    switch(pid){
        case 0:
            printf("Child process is running,CurPid is %d,ParentPid is %d\n",pid,getppid());
            break;
        case -1:
            perror("process creation failed\n");
            break;
        default:
            printf("parent process is running,Childpid is %d,parentpid is %d\n",pid,getpid());
            break;
    }
    exit(0);
}

