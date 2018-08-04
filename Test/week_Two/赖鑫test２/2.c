#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int main(int argc, char *argv[])
{
    for (int i = 0; i < 2; i++)
    {
        pid_t pid = fork();
        printf("hello, world?%d\n",getpid());
    }
    return 0;
}


/*

输出了６次，产生了加上原进程共４个进程
在第一遍循环，创建了一个子进程，父进程记为０，子进程记为１，两个进程各输出一遍
第２遍循环，进程０又创建了一个进程２，进程１也又创建了一个进程３，４个进程又各输出一遍

*/
