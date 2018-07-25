#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
int main()
{
    int fd;
	char a[20];
	scanf("%[^\n]",a);
	if((fd=creat(a,S_IRWXU))== -1)
	{
	    perror("open");
		exit(1);
	}
	else
	{
	    printf("create file success\n");
	}
	close(fd);
	return 0;
}
