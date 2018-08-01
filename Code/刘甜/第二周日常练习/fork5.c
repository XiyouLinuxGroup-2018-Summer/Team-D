/*************************************************************************
	> File Name: fork5.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月30日 星期一 14时44分20秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
int main(){
    pid_t fpid; //fpid为fork函数的返回值
    //printf("fork!\n");
    printf("fork!");
    fpid=fork();
    if(fpid<0)
        printf("error in fork!");
    else if(fpid == 0)
        printf("I am the child process,my process id is %d\n",getpid());
    else
        printf("I am the parent process,my process id is %d\n",getpid());
    return 0;
}
