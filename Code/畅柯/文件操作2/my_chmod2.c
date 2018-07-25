#include<stdio.h>
#include<time.h>
#include<unistd.h>
#include<sys/types.h>
#include<errno.h>
#include<sys/stat.h>
#include<stdlib.h>
int main(int argc , char ** argv){
	struct stat buf ;
	//检查参数个数
	if(argc!=2){
		printf("Usage:my_stat<filename>");
		exit(0);
	}
	//获取文件属性
	if(stat(argv[1],&buf)==-1){
		perror("stat:");
		exit(1);
	}
	//打印出文件属性
	printf("Device is:%d\n",buf.st_dev);
	printf("inode is:%d\n",buf.st_ino);
	printf("mode is:%o\n",buf.st_mode);
	printf("number of hard link is:%d\n",buf.st_nlink);
	printf("user ID of owner is:%d\n",buf.st_uid);
	printf("group ID of owner is:%d\n ",buf.st_gid);
	printf("device type (if inode device) is:%d\n",buf.st_rdev);
	printf("total size,in bytes is:%d\n",buf.st_size);
	printf("time of last access is:%s\n",ctime(&buf.st_atime));
	printf("time of last modification is:%s\n",ctime(&buf.st_mtime));
	printf("time of last change is:%s\n",ctime(&buf.st_ctime));
	return 0;
}

