#include <string.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
void my_err(const char * err_string,int line)
{
	fprintf(stderr,"line:%d",line);
	perror(err_string);
	exit(1);
}
int my_read(int fd)
{
		int len;
		int ret;
		int i;
		char read_buf[64];
		//获取文件长度并确保文件指针在开始位置
		if((lseek(fd,0,SEEK_SET))==-1){
			my_err("lseek",__LINE__);
		}
		if((len=lseek(fd,0,SEEK_CUR))==-1){
			my_err("lseek",__LINE__);
		}
		if((lseek(fd,0,SEEK_SET))==-1){
			my_err("lseek",__LINE__);
			}
	printf("len:%d\n",len);
	//读取文件内容
	if((ret=read(fd,read_buf,len))==-1){
		my_err("read",__LINE__);
		}
	//打印文件数据
	for(i=0;i<len;i++){
		printf("%c",read_buf[i]);
	}
	printf("\n");
	return ret;
}
int main()
{
	int fd;
	char write_buf[32]="hello world!";
	if((fd=open("test1",O_RDWR|O_CREAT|O_TRUNC,S_IRWXU))==-1){
		my_err("open",__LINE__);
	}
	//写数据
	if((write(fd,write_buf,strlen(write_buf))!=strlen(write_buf))){
		my_err("write",__LINE__);
	}
	my_read(fd);
	printf("\n-------------------\n");
	if(lseek(fd,8,SEEK_CUR)==-1){
		my_err("lseek",__LINE__);
	}
	if(write(fd,write_buf,strlen(write_buf))!=strlen(write_buf)){
		my_err("write",__LINE__);
	}
	my_read(fd);
	close(fd);
	return 0;
	close(fd);
	return 0;
}

