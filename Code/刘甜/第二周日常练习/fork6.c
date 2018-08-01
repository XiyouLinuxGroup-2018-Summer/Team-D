/*************************************************************************
	> File Name: fork6.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月30日 星期一 14时56分23秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>

int main(void)
{
    pid_t pid;
    char *msg;
    int k;

    printf("Process Creation Sutdy\n");
    pid = fork();
    switch(pid){
        case 0:
            msg = "child process is running";
            k=3;
            break;
        case -1:
            perror("process creation failed\n");
            break;
        default:
            msg = "parent process is running";
            k=5;
            break;
    }
    while(k>0)
    {
        puts(msg);
        sleep(1);
        k--;
    }
    exit(0);
}
