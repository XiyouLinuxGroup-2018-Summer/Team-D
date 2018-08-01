#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
    pid_t pid;
    char *msg;
    int k;
    printf("创建进程学习\n");
    pid=fork();
    switch(pid)
    {
    case 0:
        msg="子进程正在运行";k=3;
        break;
    case -1:
        perror("创建失败！\n");
        break;
    default:
         msg="父进程正在运行";k=5;
        break;
    }
    while(k>0)
    {
	puts(msg);
        sleep(1);  
        //printf("***\n");      
	k--;
    }

    exit(0);
    
}

//使程序挂起１秒钟，即函数滞留１秒,子进程和父进程互相抢夺ＣＰＵ，来重新执行程序，而只有在sleep前执行的进程跟之后的相同时才输出printf，否则滞后等到该进程时才输出。
//若将两个k，交换位置，则子进程会未被进行完毕，此时，可以输入命令，即可像终端一样输出！然后结束
