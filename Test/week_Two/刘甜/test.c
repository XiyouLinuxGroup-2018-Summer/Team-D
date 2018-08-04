#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
int main(int argc,char *argv[])
{
    printf("hello,my pid is %d\n",getpid());
    pid_t pid=fork();
    if(pid==0)
    {
        printf("i was forked! :D %d\n",getpid());
    }
    else
    {
        waitpid(pid,NULL,0);
        printf("%d was forked!\n",pid);
    }
    return 0;
}
3、 代码输出结果为:
    hello,my pid is 7364
    I was forked! :D 7365
    7365 was forked!
    test | cat：无显示

