#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
    pid_t pid;
    printf("创建进程学习\n");
    pid=fork();
    switch(pid)
    {
    case 0:
        printf("子进程正在运行，返回值%d,父进程是%d\n",pid,getppid());
        break;
    case -1:
        printf("创建失败\n");
        break;
    default:
        printf("父进程正在运行，子进程是%d,父进程是%d\n",pid,getpid());
        break;
    }
    exit(0);
}

//fork创建了一个子进程，也就是将再创建一个进程再执行一次此程序，所以　switch 语句被执行了两次，一次是在父进程，一次是在子进程，所以如果进程创建成功，则fork()函数有两次返回值，子进程执行时的返回值是０，父进程的返回值是新创建子进程的ＩＤ，而fork()后先执行子进程还是父进程取决于内核所使用的调度算法。
