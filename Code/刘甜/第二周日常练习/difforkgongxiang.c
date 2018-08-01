/*************************************************************************
	> File Name: difforkdongxiang.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月30日 星期一 16时28分17秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
int a = 10;
 
int main(int argc, char *argv[])
{
	pid_t pid;
	
	int b = 20;
	
	pid = vfork();	// 创建进程
	if(pid < 0){ // 出错
		perror("vfork");
	}
	
	if(0 == pid){ // 子进程
	
		a++, b++;
		printf("son: a = %d, b = %d\n", a, b);
		
		exit(0); // 退出子进程，必须
	}else if(pid > 0){ // 父进程
		a++;b++;
		printf("father: a = %d, b = %d\n", a, b);
		
	}
	
	return 0;
}
