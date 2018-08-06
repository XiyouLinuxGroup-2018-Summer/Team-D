#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
	for (int i = 0; i < 2; i++)
	{
		pid_t pid = fork();
		printf("hello, world?");
	}
	printf("\n");
 	return 0;
}

/*一共输出八次，父进程创建了子进程后会输入一个hello,world。然后子进程也会输出一次。然后子进程循环，子进程输出一次，然后子进程创建的子进程也会输出一次。父进程开始循环，输出一次，然后父进程又创建了一个子进程，子进程再输出一次。
 * 一共产生了四个进程，父进程，两个子进程，一个子进程创建的子进程。*/
