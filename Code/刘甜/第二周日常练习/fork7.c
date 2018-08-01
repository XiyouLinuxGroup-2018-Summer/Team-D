/*************************************************************************
	> File Name: fork7.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月30日 星期一 15时25分38秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>

int main(void)
{
    pid_t pid;
    pid = fork();
    switch(pid){
        case 0:
            while(1){
                printf("A backgroud process,PID:%d\n,parentID:%d\n",getpid(),getppid());
            sleep(3);
            }
        case -1:
            perror("process creation failed\n");
            exit(-1);
        default:
            printf("I am parent process,my pid is %d\n",getpid());
            exit(0);
    }
    return 0;
}
