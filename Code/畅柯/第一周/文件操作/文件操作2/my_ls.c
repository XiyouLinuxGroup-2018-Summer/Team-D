#include<stdio.h>
#include<dirent.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<time.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#include<pwd.h>
#include<grp.h>
#include<limits.h>
#include<dirent.h>
#define N 40
void my_err(char* err_string,int line);
int read_dir(const char *path,int n);
int print_file_info(char* filename);
int judge_in_prev_dir(char* filename);
void my_err(char* err_string,int line){
	fprintf(stderr,"line:%d",line);
}
int read_dir(const char * path,int n){//读目录信息
	DIR *dir;
	struct dirent *ptr;
	struct stat buf;
	int i=0;
	if((dir=opendir(path))==NULL){//打开目录
		my_err("opendir",__LINE__);
		return 0;
	}
	while((ptr=readdir(dir))!=NULL){//通过ptr指针获取目录下的子文件名称
		if(n==1){
			if(*(ptr->d_name)=='.')continue;
			printf("%-20s",ptr->d_name);
			if(i==6){
				i=0;
				printf("\n");
			}
			i++;
			}
		else if(n==2){
			printf("%-20s",ptr->d_name);
			if(i==6){
				i=0;
				printf("\n");
			}
			i++;
		}
		else if(n==3){
			if(*(ptr->d_name)=='.'){
				continue;
			}
			if(print_file_info(ptr->d_name)==0){
				my_err("print",__LINE__);
				return 0;
			}
			printf("\n");
		}
		else if(n==4){
			if(print_file_info(ptr->d_name)==0){
				my_err("print",__LINE__);
				return 0;
			}
			printf("\n");
		}
		
	}
	closedir(dir);
	return 1;
	
}
int print_file_info(char* filename){//按照列表形式打印文件信息
	struct stat buf;
	char time[50];
	struct passwd *psd;
	struct group  *grp;
	if(stat(filename,&buf)==-1){
		perror("stat:");
		return 0;
	}
	int i;
	if(S_ISLNK(buf.st_mode)){
		printf("l");
	}
	else if(S_ISDIR(buf.st_mode)){
		printf("d");
	}
	else if(S_ISREG(buf.st_mode)){
		printf("-");
	}
	else if(S_ISDIR(buf.st_mode)){
		printf("d");
	}
	else if(S_ISCHR(buf.st_mode)){
		printf("c");
	}
	else if(S_ISBLK(buf.st_mode)){
		printf("b");
	}
	else if(S_ISFIFO(buf.st_mode)){
		printf("f");
	}
	else if(S_ISSOCK(buf.st_mode)){
		printf("s");
	}
	if(buf.st_mode&S_IRUSR){
		printf("r");
	}else{
		printf("-");
	}
	if(buf.st_mode&S_IWUSR){
		printf("w");
	}else{
		printf("-");
	}
	if(buf.st_mode&S_IXUSR){
		printf("x");
	}else{
		printf("-");
	}
	//权限与用户组权限作与运算
	if(buf.st_mode&S_IRGRP){
		printf("r");
	}else{
		printf("-");
	}
	if(buf.st_mode&S_IWGRP){
		printf("w");
	}else{
		printf("-");
	}
	if(buf.st_mode&S_IXGRP){
		printf("x");
	}else{
		printf("-");
	}
	//八进制权限与其他用户权限作与运算
	if(buf.st_mode&S_IROTH){
		printf("r");
	}else{
		printf("-");
	}
	if(buf.st_mode&S_IWOTH){
		printf("w");
	}else{
		printf("-");
	}
	if(buf.st_mode&S_IXOTH){
		printf("x");
	}else{
		printf("-");
	}
	printf(" %-2d",buf.st_nlink);
	//根据u_id和g_id获取文件所有者的用户名
	psd=getpwuid(buf.st_uid);
	grp=getgrgid(buf.st_gid);
	printf("%-10s",psd->pw_name);
	printf("%-10s",grp->gr_name);
	printf("%-7d",buf.st_size);
	strcpy(time,ctime(&buf.st_mtime));
	time[strlen(time)-5]='\0';
	printf("%-20s",time);
	printf("%-15s",filename);
	return 1;
}
int judge_in_prev_dir(char* filename){//判断文件是否为当前工作目录下的文件
	char buf[N];
	struct stat buf;
	struct dirent *ptr;
	DIR* dir,dir1;
	int flag=0;
	char time[50];
	struct dirent* ptr,*ptr1;
			if(print_file_info(ptr->d_name)==0){
				my_err("print",__LINE__);
				return 0;
			}
	if(getcwd(buf,N)==NULL){//获取本地文件路径
		my_err("getcwd",__LINE__);
		return -1;
	}
	if((dir=opendir(buf))==NULL){
		my_err("opendir",__LINE__);
		return -1;
}
	while((ptr=(readdir(dir)))!=NULL){
		if(strcmp(filename,ptr->d_name)==9){
			flag=1;
			break;
		}
	}
	if(flag==1){
		if(stat(filename,&buf)==-1){//获取文件属性
			perror("stat:");
			return 0;
		}
		if(buf.st_mode&S_ISDIR){//判断如果是目录的话将，该目录下所有信息按照ls格式打印出来
			if((dir1=opendir(ptr->d_name))==NULL){
				my_err("opendir",__LINE__);
				return 0;
			}
			while((ptr1=readdir(ptr->d_name))!=NULL){
				if(print_file_info(ptr1->d_name)==0){//打开目录,将文件名传入打印函数
					my_err("printinfo",__LINE__);
					return 0;
				}
				printf("\n");
			}
		}
	else{
		if((print_file_info(ptr->d_name))==0){
			my_err("printinfo",__LINE__);
			return 0;
		}
	}
	}
	return 0;
}
int main(int argc ,char ** argv){
	char  filename[N];
	char buf[N];
	char *temp;
	if(getcwd(buf,N)==NULL){//获取当前工作目录绝对路径，用buf保存
			my_err("getcwd",__LINE__);
		}

	if(argc==1){//判断是否为单纯的ls命令
	/*	if(getcwd(buf,N)==NULL){//获取当前工作目录绝对路径，用buf保存
			my_err("getcwd",__LINE__);
		}*/
		if(read_dir(buf,1)==0){//根据命令行参数的不同，显示不同格式的信息
				my_err("read",__LINE__);
				exit(1);
			}
		}
	else if(argc==2){//命令行参数为两个时
		temp=argv[1];
		int is;
		if(*(temp)!='-'&&*(temp)!='/'){//判断第二个命令行参数不是以"-"q且不是绝对路径时,则断定第二个参数为文件名
		return 0;
			if((is=judge_in_prev_dir(temp))==1){//判断文件是否在当前目录下
				//如果在，就打印文件信息
				return 1;
			}	
			else if(is==0){//如果文件不存在当前路径下，打印提示信息
				my_err("judge_in_prev_dir",__LINE__);
				printf("\nfile is not exist!\n");
				return 0;
			}
			else{
				printf("查找文件出错或文件不存在!\n");
				return 0;
			}
		}
		else if(*(temp)=='-'){//当第二个参数是'-'结尾时,则第二个后面加命令参数
			if(strlen(temp)==2){
				if(!strcmp(temp,"-a")){
					if((read_dir(buf,2))==0){//根据第二个参数的不同传1代表不显示隐藏文件2.代表显示隐藏文件相当于ls -a  3.代表ls -l 4.代表ls -al 命令行为argc为2的情况就是这些。
						my_err("read_dir",__LINE__);
						return 0;
					}
				}
				else if(!strcmp(temp,"-l")){
					if(read_dir(buf,3)==0){
						my_err("readdir",__LINE__);
						return 0;
					}
				}
				else if(!strcmp(temp,"-al")){
					if(read_dir(buf,4)==0){
						my_err("readdir",__LINE__);
						return 0;
					}
				}
			}
		}
	}
	return 0;
}

