#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
int main(int argc, char *argv[])
{
    printf("Hello, my pid is %d\n", getpid());
    pid_t pid = fork();
    if (pid == 0)
    {
        printf("I was forked! :D %d\n", getpid());
    }
    else
    {
        waitpid(pid, NULL, 0);
        printf("%d was forked!\n", pid);
    }
    return 0;


/*
输出结果为：
Hello, my pid is 26802
I was forked! :D 26803
26803 was forked!

test | cat 结果为：
Hello, my pid is 26802
I was forked! :D 26803
Hello, my pid is 26802
26803 was forked!
多了一条最开始的输出语句，并且是父进程的,main()函数后加上命令


