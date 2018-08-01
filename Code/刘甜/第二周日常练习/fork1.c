/*************************************************************************
	> File Name: fork1.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月30日 星期一 11时34分11秒
 ************************************************************************/

#include <unistd.h>
#include<sys/types.h>
#include <stdio.h>   
int main ()   
{   
    pid_t fpid; //fpid表示fork函数返回的值  
    int count=0;  
    fpid=fork();   
    if (fpid < 0)   
        printf("error in fork!\n");   
    else if (fpid == 0) {  
        printf("我是子进程, 我的进程id 为 %d\n",getpid()); 
        printf("fork返回值：%d\n",fpid);
        count++;  
    }  
    else {  
        printf("我是父进程, 我的进程id 为 %d\n",getpid());
        printf("fork返回值：%d\n",fpid);  
        count++;  
    }  
    printf("统计结果是: %d\n",count);  
    return 0;  
}  
