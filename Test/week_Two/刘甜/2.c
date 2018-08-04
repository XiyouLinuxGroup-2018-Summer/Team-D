#include<stdio.h>
#include<unistd.h>
int main(int argc,char *argv[])
{
    for(int i=0;i<2;i++)
    {
        pid_t pid =fork();
        printf("hello,world?\n");
    }
    return 0;
}
分析:首先进行第一次循环，当前进程产生一个子进程1，父进程和子进程分别输出一次hello,world?然后第二次循环，父进程再产生一个子进程2，子进程1经过fork再产生一个子进程3。
   a,最终输出6次"hello,world".
   b,最终将产生四个进程
