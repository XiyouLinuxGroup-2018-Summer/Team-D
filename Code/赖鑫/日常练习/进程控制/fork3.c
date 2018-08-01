#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
    pid_t pid;
    pid=fork();
    switch(pid)
    {
        case 0:
            while(1)
            {
                printf("后台进程为：PID: %d\t,父进程ＩＤ: %d \n",getpid(),getppid());
                sleep(3);
            }
        case -1:
            perror("创建进程失败\n");
            exit(-1);
        default:
            printf("我是父进程，ＩＤ为:%d\n",getpid());
            exit(0);

    }
    return 0;
}

//孤儿进程：当父进程被执行时，直接结束父进程时，当子进程被执行时，sleep()函数执行，使程序挂起，两个进程争夺cpu,而父进程执行后就结束了，只剩子进程，此时子进程便成为孤儿进程,被init进程收养，而init进程会循环地wait()它的已经退出的子进程
