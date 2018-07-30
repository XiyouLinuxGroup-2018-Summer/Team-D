#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
int main(){
	int fd;
	char str[50];
	printf("Input file name:");
	scanf("%[^\n]",str);
	if(fd=open(str,O_CREAT|O_EXCL,S_IRUSR|S_IWUSR)==-1){
		perror("open");
		exit(1);
	}
	else{
		printf("create file success!\n");
	}
	close(fd);
	return 0;
}

