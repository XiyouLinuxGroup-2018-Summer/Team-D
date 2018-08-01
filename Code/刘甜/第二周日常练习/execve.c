#include<stdio.h>
#include<stdlib.h>
#include <sys/wait.h>
#include<sys/types.h>
#include<unistd.h>

int main(int argc,char * argv[],char ** environ)
{
    pid_t pid;
    int stat_val;
    printf("Exec example!\n");
    pid = fork();
    switch(pid){
        case -1:
            perror("process creation failed\n");
            exit(1);
        case 0:
            printf("childprocess is running\n");
            printf("My pid = %d,parentpid = %d\n",getpid(),getppid());
            printf("uid = %d,gid = %d\n",getuid(),getgid());
            execve("processimage",argv,environ);
            printf("process never go to here!\n");
            exit(0);
        default:
            printf("parent process is running\n");
            break;
    }
    wait(&stat_val);
    exit(0);
}

