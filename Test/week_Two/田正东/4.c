#include<stdio.h>
#include<unistd.h>
#include<wait.h>
int main()
{
    printf("Hello,my pid is %d\n",getpid());

    pid_t pid =fork();
    if(pid == 0)
    {
        printf("I was forked : D %d\n",getpid());
    }
    else
    {
        waitpid(pid,NULL,0);
        printf("%d was forked \n",pid);
    }
    return 0;
}

/*输出结果是
 * Hello,my pid is 27896
   I was forked : D 27897
   27897 was forked

  执行test | cat后的结果为
  Hello,my pid is 27911
  I was forked : D 27913
  Hello,my pid is 27911
  27913 was forked 

  因为调用了waitpid，所以父进程会等待子进程结束，所以执行结果是三行，用了test | cat后第一句多输出了一次，cat调用重定向,子进程结束后父进程部分重新判断将父进程部分全部打印输出*/
