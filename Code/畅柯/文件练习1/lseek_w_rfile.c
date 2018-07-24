#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>

void my_err(const char* err_string,int line){
	fprintf(stderr,"line:%d",line);
	perror(err_string);
	exit(1);
}
int my_read(int fd){
	int len;
	int i;
	int ret;
	char  read_buf[60];
	//获取文件长度，并保证文件指针移动到开始位置
	if(lseek(fd,0,SEEK_SET)==-1){
		my_err("lseek",__LINE__);
	}
	if(len=lseek(fd,0,SEEK_CUR)==-1){
			my_err("lseek",__LINE__);			
			}
	if(lseek(fd,0,SEEK_END)==-1){
		my_err("lseek",__LINE__);
	}
	printf("len:%d\n",len);
	//从开始出读取文件内容
	if(ret=read(fd,read_buf,len)<0){
		my_err("read",__LINE__);
	}
	//打印数据
	for(i=0;i<len;i++){
		printf("%c",read_buf[i]);
	}
	printf("\n");
	return ret;
}
int main(){
	int fd;
	char filename[50];
	char write_buf[32]="Hello World!";
	//在当前目录下创建文件
	printf("Input read file name:");
	scanf("%[^\n]",filename);
	/*if((fd=creat(filename,S_IRWXU))==-1){
		my_err("open",__LINE__);
	}*/
	if((fd=open(filename,O_RDWR|O_CREAT|O_TRUNC,S_IRWXU))==-1){
		my_err("open",__LINE__);
	}

	else{
		printf("Create file success!\n");
	}
	/*写数据*/
	if(write(fd,write_buf,strlen(write_buf))!=strlen(write_buf)){
		my_err("write",__LINE__);
	}
	my_read(fd);
	if(lseek(fd,1,SEEK_END)==-1){
		my_err("lseek",__LINE__);
	}
	if(write(fd,write_buf,strlen(write_buf))!=strlen(write_buf)){
		my_err("write",__LINE__);
	}
	my_read(fd);
	close(fd);
	return 0;
}
