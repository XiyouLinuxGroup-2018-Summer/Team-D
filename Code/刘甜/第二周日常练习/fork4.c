/*************************************************************************
	> File Name: fork4.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月30日 星期一 14时34分11秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
int main(void)
{
    int i=0;
    for(i=0;i<3;i++){
        pid_t fpid=fork();
        if(fpid==0)
            printf("son\n");
        else 
            printf("father\n");
    }
}
