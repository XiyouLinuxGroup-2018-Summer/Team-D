/*实现my_ls -l -a -al (ls+filename/directoy尚未实现不同文件不同颜色显示) */
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
#include"list.h"
#include<limits.h>
#include<dirent.h>
#define N 10000
typedef struct fileinfo{
	char dirname[N];//文件所属目录名
	char filename[N];
	char mode[N];//文件的存取权限
	int linkNum;//连接数
	char usr[N];//所属用户
	char grp[N];//所属组
	int flag;//根据flag的值实现文件名颜色设置
	int size;//所占空间大小
	char time[N];//最后修改时间
}file_t;
typedef struct filenode{//创建双向链表结构体
	file_t data;
	struct filenode * next;
	struct filenode * prev;
}file_node_t;

int list_by_file(char * dirname,int num);
int print_all_info(int num,file_node_t* h);
int file_list_sort(file_node_t*h ,int num);
int get_all_file_info(file_node_t*h,const char* dirname,int num);
void my_err(char* err_string,int line);

int judge_in_prev_dir(char* filename);
int get_property(struct stat buf);//传入文件名,获取文件属性
int list_by_file(char* dirname,int num){
	DIR* dir;//接收目录信息
	int i;
	struct dirent *ptr;//接受目录下面文件信息
	struct stat buf;//获取文件属性
	struct passwd *psd;//获取所属用户名
	struct group* grp;//获取所属组名称
	file_node_t *h,*p;
	List_Init(h,file_node_t);
	if(lstat(dirname,&buf)==-1){
		return -1;
	}
	if(S_ISDIR(buf.st_mode)==0){
		return -1;
	}
	if((dir=opendir(dirname))==NULL){
		my_err("opendir",__LINE__);
		return -1;
	}
	chdir(dirname);
	strcpy(h->data.dirname,dirname);
	while((ptr=readdir(dir))!=NULL){
		i=0;
		p=(file_node_t*)malloc(sizeof(file_node_t));
		if(lstat(ptr->d_name,&buf)==-1){//获取文件属性
			my_err("stat:",__LINE__);
			return -1;
		}
		if(!strcmp(ptr->d_name,"..")||!strcmp(ptr->d_name,".")){
			p->data.flag= 33;
			(*(p->data.mode+i))='d';		
			i++;
			if(buf.st_mode&S_IRUSR){

				(*(p->data.mode+i))='r';		
			}else{
				(*(p->data.mode+i))='-';		
			}
			i++;
			if(buf.st_mode&S_IWUSR){
				(*(p->data.mode+i))='w';		
			}else{
				(*(p->data.mode+i))='-';		
			}
			i++;
			if(buf.st_mode&S_IXUSR){
				(*(p->data.mode+i))='x';		
			}else{
				(*(p->data.mode+i))='-';		
			}
			i++;
	//权限与用户组权限作与运算
			if(buf.st_mode&S_IRGRP){
				(*(p->data.mode+i))='r';		
			}else{
				(*(p->data.mode+i))='-';		
			}
			i++;
			if(buf.st_mode&S_IWGRP){
				(*(p->data.mode+i))='w';		
			}else{
				(*(p->data.mode+i))='-';		
			}

			i++;
			if(buf.st_mode&S_IXGRP){
				(*(p->data.mode+i))='x';		
			}else{
				(*(p->data.mode+i))='-';		
			}
			i++;
		//八进制权限与其他用户权限作与运算
			if(buf.st_mode&S_IROTH){
				(*(p->data.mode+i))='r';		
			}else{
				(*(p->data.mode+i))='-';		
			}
			i++;
			if(buf.st_mode&S_IWOTH){
				(*(p->data.mode+i))='w';		
			}else{
				(*(p->data.mode+i))='-';		
			}
			i++;
			if(buf.st_mode&S_IXOTH){
				(*(p->data.mode+i))='x';		
			}else{
				(*(p->data.mode+i))='-';		
			}
			i++;
			(*(p->data.mode+i))='\0';	

			p->data.linkNum=buf.st_nlink;
		
			psd=getpwuid(buf.st_uid);
			strcpy(p->data.usr,psd->pw_name);

			grp=getgrgid(buf.st_gid);
			strcpy(p->data.grp,grp->gr_name);
			p->data.size=buf.st_size;
			strcpy(p->data.time,ctime(&buf.st_mtime));
			p->data.time[strlen(p->data.time)-5]='\0';
			strcpy(p->data.filename,ptr->d_name);
			continue;
			}
		if(S_ISLNK(buf.st_mode)){
			p->data.flag=32;
			(*(p->data.mode+i))='l';		
		}
		else if(S_ISDIR(buf.st_mode)){
			
			p->data.flag= 33;
			(*(p->data.mode+i))='d';		
		}
		else if(S_ISREG(buf.st_mode)){
			p->data.flag==1;
			(*(p->data.mode+i))='-';		
		}
		else if(S_ISCHR(buf.st_mode)){
			p->data.flag=35;		
			(*(p->data.mode+i))='c';		
		}
		else if(S_ISBLK(buf.st_mode)){
			p->data.flag=35;
			(*(p->data.mode+i))='b';		
		}
		else if(S_ISFIFO(buf.st_mode)){
			p->data.flag=35;
			(*(p->data.mode+i))='f';		
		
		}
		else if(S_ISSOCK(buf.st_mode)){
			(*(p->data.mode+i))='s';		
			p->data.flag=35;
		}
		i++;
		if(buf.st_mode&S_IRUSR){

			(*(p->data.mode+i))='r';		
		}else{
			(*(p->data.mode+i))='-';		
		}
		i++;
		if(buf.st_mode&S_IWUSR){
			(*(p->data.mode+i))='w';		
		}else{
			(*(p->data.mode+i))='-';		
		}
		i++;
		if(buf.st_mode&S_IXUSR){
			(*(p->data.mode+i))='x';		
		}else{
			(*(p->data.mode+i))='-';		
		}
		i++;
	//权限与用户组权限作与运算
		if(buf.st_mode&S_IRGRP){
			(*(p->data.mode+i))='r';		
		}else{
			(*(p->data.mode+i))='-';		
		}
		i++;
		if(buf.st_mode&S_IWGRP){
			(*(p->data.mode+i))='w';		
		}else{
			(*(p->data.mode+i))='-';		
		}

		i++;
		if(buf.st_mode&S_IXGRP){
			(*(p->data.mode+i))='x';		
		}else{
			(*(p->data.mode+i))='-';		
		}
		i++;
		//八进制权限与其他用户权限作与运算
		if(buf.st_mode&S_IROTH){
			(*(p->data.mode+i))='r';		
		}else{
			(*(p->data.mode+i))='-';		
		}
		i++;
		if(buf.st_mode&S_IWOTH){
			(*(p->data.mode+i))='w';		
		}else{
			(*(p->data.mode+i))='-';		
		}
		i++;
		if(buf.st_mode&S_IXOTH){
			(*(p->data.mode+i))='x';		
		}else{
			(*(p->data.mode+i))='-';		
		}
		i++;
		(*(p->data.mode+i))='\0';	

		if(S_ISREG(buf.st_mode)&&(buf.st_mode&S_IXUSR)){//若文件有可执行属性且为普通文件，则文件为可执行文件
			p->data.flag=36;
		}
		
		p->data.linkNum=buf.st_nlink;
		
		psd=getpwuid(buf.st_uid);
		strcpy(p->data.usr,psd->pw_name);

		grp=getgrgid(buf.st_gid);
		strcpy(p->data.grp,grp->gr_name);
		p->data.size=buf.st_size;
		strcpy(p->data.time,ctime(&buf.st_mtime));
		p->data.time[strlen(p->data.time)-5]='\0';
		strcpy(p->data.filename,ptr->d_name);
		if(p->data.flag==33){//判断当前文件是否为目录文件
			if(0==list_by_file(ptr->d_name,num)){
				printf("\n");
			}
		}
		List_AddTail(h,p);//将文件数据存入链表*/
	}
	file_sort_info(h,num);
	List_Free(h,file_node_t);
	chdir("..");
	closedir(dir);
	return 0;
}
int print_all_info(int num,file_node_t* h){
	long allsize=0;
	long allsize1=0;
	int i=0;
	char buf[N];
	file_node_t*temp,*temp1;
	temp1=h->next;
	while(temp1!=h){
		allsize++;
		temp1=temp1->next;
		if(*(temp->data.filename)!='.'){
			allsize1++;
		}
	}
//	allsize1=allsize1/512;
//	allsize=allsize/512;
	temp=h->next;
	
	switch(num){
		case 1://ls 
			while(temp!=h){
				if(*(temp->data.filename)=='.'){
					temp=temp->next;
					continue;
				}
				i++;
				
				switch(temp->data.flag){
					case 32:
						printf("\033[32m %-15s\033[0m",temp->data.filename);
						break;
					case 33:
						printf("\033[33m %-15s\033[0m",temp->data.filename);
						break;
					case 36:
						printf("\033[36m %-15s\033[0m",temp->data.filename);
						break;
					case 35:
						printf("\033[35m %-15s\033[0m",temp->data.filename);
						break;
					default:
						printf("%-15s",temp->data.filename);
						break;
					}
					if(i==6){
						i=0;
						printf("\n");
					}
					temp=temp->next;
			}
			printf("\n");
			break;
		case 2://ls -al
			printf("总用量:%ld\n",allsize);
			while(temp!=h){
				printf("%-15s",temp->data.mode);
				printf("%-5d",temp->data.linkNum);
				printf("%-15s",temp->data.usr);
				printf("%-15s",temp->data.grp);
				printf("%-8d",temp->data.size);
				printf("%-15s",temp->data.time);
				
				switch(temp->data.flag){
					case 32:
						printf("\033[32m %-15s\033[0m",temp->data.filename);
						break;
					case 33:
						printf("\033[33m %-15s\033[0m",temp->data.filename);
						break;
					case 36:
						printf("\033[36m %-15s\033[0m",temp->data.filename);
						break;
					case 35:
						printf("\033[35m %-15s\033[0m",temp->data.filename);
						break;
					default:
						printf("%-15s",temp->data.filename);
						break;
			}
				temp=temp->next;
				printf("\n");
			}
			break;
		case 3://ls -l
			printf("总用量:%ld\n",allsize1);
			while(temp!=h){

				if(*(temp->data.filename)=='.'){
					temp=temp->next;
					continue;
				}
				printf("%-15s",temp->data.mode);
				printf("%-5d",temp->data.linkNum);
				printf("%-15s",temp->data.usr);
				printf("%-15s",temp->data.grp);
				printf("%-8d",temp->data.size);
				printf("%-15s",temp->data.time);
				
				switch(temp->data.flag){
					case 32:
						printf("\033[32m %-15s\033[0m",temp->data.filename);
						break;
					case 33:
						printf("\033[33m %-15s\033[0m",temp->data.filename);
						break;
					case 36:
						printf("\033[36m %-15s\033[0m",temp->data.filename);
						break;
					case 35:
						printf("\033[35m %-15s\033[0m",temp->data.filename);
						break;
					default:
						printf("%-15s",temp->data.filename);
						break;
			}
				temp=temp->next;
				printf("\n");
		}
			break;
		case 4://ls -a
			while(temp!=h){
				i++;
				switch(temp->data.flag){
					case 32:
						printf("\033[32m %-15s\033[0m",temp->data.filename);
						break;
					case 33:
						printf("\033[33m %-15s\033[0m",temp->data.filename);
						break;
					case 36:
						printf("\033[36m %-15s\033[0m",temp->data.filename);
						break;
					case 35:
						printf("\033[35m %-15s\033[0m",temp->data.filename);
						break;
					default:
						printf("%-15s",temp->data.filename);
						break;
			}
				if(i==6){
					printf("\n");
					i=0;
				}
				
				temp=temp->next;

			}
			printf("\n");
			break;
		case 5:
			printf("%-50s总用量:%d\n",h->data.dirname,allsize);
			while(temp!=h){
				printf("%-15s",temp->data.mode);
				printf("%-5d",temp->data.linkNum);
				printf("%-15s",temp->data.usr);
				printf("%-15s",temp->data.grp);
				printf("%-8d",temp->data.size);
				printf("%-15s",temp->data.time);
				
				switch(temp->data.flag){
					case 32:
						printf("\033[32m %-15s\033[0m",temp->data.filename);
						break;
					case 33:
						printf("\033[33m %-15s\033[0m",temp->data.filename);
						break;
					case 36:
						printf("\033[36m %-15s\033[0m",temp->data.filename);
						break;
					case 35:
						printf("\033[35m %-15s\033[0m",temp->data.filename);
						break;
					default:
						printf("%-15s",temp->data.filename);
						break;
			}
				temp=temp->next;
				printf("\n");
			}
			break;
		case 6:
			if(getcwd(buf,N)<0){
				my_err("getcwd",__LINE__);
				return 0;
			}
			printf("%-50s总用量：%-5d\n",h->data.dirname,allsize1);	
			while(temp!=h){
				
				if(*(temp->data.filename)=='.'){
					temp=temp->next;
					continue;
				}
				i++;
				switch(temp->data.flag){
					case 32:
						printf("\033[32m %-15s\033[0m",temp->data.filename);
						break;
					case 33:
						printf("\033[33m %-15s\033[0m",temp->data.filename);
						break;
					case 36:
						printf("\033[36m %-15s\033[0m",temp->data.filename);
						break;
					case 35:
						printf("\033[35m %-15s\033[0m",temp->data.filename);
						break;
					default:
						printf("%-15s",temp->data.filename);
						break;
				}
				temp=temp->next;
				if(i==6){
					printf("\n");
					i=0;
				}
			}
			printf("\n");
			break;
		case 7:
			while(temp!=h){
				i++;
				switch(temp->data.flag){
					case 32:
						printf("\033[32m %-15s\033[0m",temp->data.filename);
						break;
					case 33:
						printf("\033[33m %-15s\033[0m",temp->data.filename);
						break;
					case 36:
						printf("\033[36m %-15s\033[0m",temp->data.filename);
						break;
					case 35:
						printf("\033[35m %-15s\033[0m",temp->data.filename);
						break;
					default:
						printf("%-15s",temp->data.filename);
						break;
				}
				if(i==6){
					i=0;
					printf("\n");
				}
			}
			printf("\n");
			break;
		case 8:
			printf("%-50s总用量:%ld\n",h->data.dirname,allsize1);
			while(temp!=h){

				if(*(temp->data.filename)=='.'){
					temp=temp->next;
					continue;
				}
				printf("%-15s",temp->data.mode);
				printf("%-5d",temp->data.linkNum);
				printf("%-15s",temp->data.usr);
				printf("%-15s",temp->data.grp);
				printf("%-8d",temp->data.size);
				printf("%-15s",temp->data.time);
				
				switch(temp->data.flag){
					case 32:
						printf("\033[32m %-15s\033[0m",temp->data.filename);
						break;
					case 33:
						printf("\033[33m %-15s\033[0m",temp->data.filename);
						break;
					case 36:
						printf("\033[36m %-15s\033[0m",temp->data.filename);
						break;
					case 35:
						printf("\033[35m %-15s\033[0m",temp->data.filename);
						break;
					default:
						printf("%-15s",temp->data.filename);
						break;
			}
				temp=temp->next;
				printf("\n");
			}
			break;
		case 9:
			printf("%-50s总用量:%ld\n",h->data.dirname,allsize1);
			while(temp!=h){
				if(*(temp->data.filename)=='.'){
					temp=temp->next;
					continue;
				}
				printf("%-15s",temp->data.mode);
				printf("%-5d",temp->data.linkNum);
				printf("%-15s",temp->data.usr);
				printf("%-15s",temp->data.grp);
				printf("%-8d",temp->data.size);
				printf("%-15s",temp->data.time);
				
				switch(temp->data.flag){
					case 32:
						printf("\033[32m %-15s\033[0m",temp->data.filename);
						break;
					case 33:
						printf("\033[33m %-15s\033[0m",temp->data.filename);
						break;
					case 36:
						printf("\033[36m %-15s\033[0m",temp->data.filename);
						break;
					case 35:
						printf("\033[35m %-15s\033[0m",temp->data.filename);
						break;
					default:
						printf("%-15s",temp->data.filename);
						break;
			}
				temp=temp->next;
				printf("\n");
			}
		break;		
	}
	
	return 1;
}

int file_sort_info(file_node_t *h,int num){//用冒泡排序对文件名进行排序
	file_node_t* temp,*pro,*swap,*q;
	swap=(file_node_t*)malloc(sizeof(file_node_t));
	temp=h->next;
	q=h;
	while(temp!=q){
		pro=temp;
		while(pro->next!=q){//链表交换数据域
			if(strcmp(pro->data.filename,pro->next->data.filename)>0){
				strcpy(swap->data.filename,pro->data.filename);
				strcpy(swap->data.mode,pro->data.mode);
				swap->data.linkNum=pro->data.linkNum;
				strcpy(swap->data.usr,pro->data.usr);
				strcpy(swap->data.grp,pro->data.grp);
				swap->data.flag=pro->data.flag;
				swap->data.size=pro->data.size;
				strcpy(swap->data.time,pro->data.time);
				
				strcpy(pro->data.filename,pro->next->data.filename);
				strcpy(pro->data.mode,pro->next->data.mode);
				pro->data.linkNum=pro->next->data.linkNum;
				strcpy(pro->data.usr,pro->next->data.usr);
				strcpy(pro->data.grp,pro->next->data.grp);
				pro->data.flag=pro->next->data.flag;
				pro->data.size=pro->next->data.size;
				strcpy(pro->data.time,pro->next->data.time);

				strcpy(pro->next->data.filename,swap->data.filename);
				strcpy(pro->next->data.mode,swap->data.mode);
				pro->next->data.linkNum=swap->data.linkNum;
				strcpy(pro->next->data.usr,swap->data.usr);
				strcpy(pro->next->data.grp,swap->data.grp);
				pro->next->data.flag=swap->data.flag;
				pro->next->data.size=swap->data.size;
				strcpy(pro->next->data.time,swap->data.time);
			}

			pro=pro->next;
		}
		q=q->prev;
	}

	file_node_t*p;
	p=h->next;
	free(swap);
	print_all_info(num,h);
}
int get_all_file_info(file_node_t *h,const char* dirname,int num){//1.ls 2.ls
	char path[N]; 
	
	file_node_t *p;//用链表将数据保存
	List_Init(h,file_node_t);
	DIR *dir;//接收目录信息
	struct dirent *ptr;//接受文件下面的目录信息
	struct stat buf;//获取文件属性
	struct passwd *psd;//根据文件属性找用户名
	struct group * grp;//根据属性找用户组名
	int i;
	if((dir=(opendir(dirname)))==NULL){
		my_err("opendir",__LINE__);
		return 0;
	}
		
	if(chdir(dirname)<0){
		my_err("chdir",__LINE__);
		return 0;
	}
	while((ptr=readdir(dir))!=NULL){
		p=(file_node_t*)malloc(sizeof(file_node_t));
		i=0;
		if(lstat(ptr->d_name,&buf)==-1){//获取文件属性
			my_err("stat:",__LINE__);
			return 0;
		}
		if(S_ISLNK(buf.st_mode)){
			p->data.flag=32;
			(*(p->data.mode+i))='l';		
		}
		else if(S_ISDIR(buf.st_mode)){
			
			p->data.flag= 33;
			(*(p->data.mode+i))='d';		
		}
		else if(S_ISREG(buf.st_mode)){
			p->data.flag==1;
			(*(p->data.mode+i))='-';		
		}
		else if(S_ISCHR(buf.st_mode)){
			p->data.flag=35;		
			(*(p->data.mode+i))='c';		
		}
		else if(S_ISBLK(buf.st_mode)){
			p->data.flag=35;
			(*(p->data.mode+i))='b';		
		}
		else if(S_ISFIFO(buf.st_mode)){
			p->data.flag=35;
			(*(p->data.mode+i))='f';		
		
		}
		else if(S_ISSOCK(buf.st_mode)){
			(*(p->data.mode+i))='s';		
			p->data.flag=35;
		}
		i++;
		if(buf.st_mode&S_IRUSR){

			(*(p->data.mode+i))='r';		
		}else{
			(*(p->data.mode+i))='-';		
		}
		i++;
		if(buf.st_mode&S_IWUSR){
			(*(p->data.mode+i))='w';		
		}else{
			(*(p->data.mode+i))='-';		
		}
		i++;
		if(buf.st_mode&S_IXUSR){
			(*(p->data.mode+i))='x';		
		}else{
			(*(p->data.mode+i))='-';		
		}
		i++;
	//权限与用户组权限作与运算
		if(buf.st_mode&S_IRGRP){
			(*(p->data.mode+i))='r';		
		}else{
			(*(p->data.mode+i))='-';		
		}
		i++;
		if(buf.st_mode&S_IWGRP){
			(*(p->data.mode+i))='w';		
		}else{
			(*(p->data.mode+i))='-';		
		}
		i++;
		if(buf.st_mode&S_IXGRP){
			(*(p->data.mode+i))='x';		
		}else{
			(*(p->data.mode+i))='-';		
		}
		i++;
		//八进制权限与其他用户权限作与运算
		if(buf.st_mode&S_IROTH){
			(*(p->data.mode+i))='r';		
		}else{
			(*(p->data.mode+i))='-';		
		}
		i++;
		if(buf.st_mode&S_IWOTH){
			(*(p->data.mode+i))='w';		
		}else{
			(*(p->data.mode+i))='-';		
		}
		i++;
		if(buf.st_mode&S_IXOTH){
			(*(p->data.mode+i))='x';		
		}else{
			(*(p->data.mode+i))='-';		
		}
		i++;
		(*(p->data.mode+i))='\0';	

		if(S_ISREG(buf.st_mode)&&(buf.st_mode&S_IXUSR)){//若文件有可执行属性且为普通文件，则文件为可执行文件
			p->data.flag=36;
		}
		p->data.linkNum=buf.st_nlink;
	
		psd=getpwuid(buf.st_uid);
		strcpy(p->data.usr,psd->pw_name);
		grp=getgrgid(buf.st_gid);
		strcpy(p->data.grp,grp->gr_name);
		p->data.size=buf.st_size;

		strcpy(p->data.time,ctime(&buf.st_mtime));
		p->data.time[strlen(p->data.time)-5]='\0';
		strcpy(p->data.filename,ptr->d_name);
		List_AddTail(h,p);//将文件数据存入链表*/
	}

	if(file_sort_info(h,num)==0){
		my_err("sort",__LINE__);
		return 0;
	}
	closedir(dir);
	return 1;

}

int get_property(struct stat buf){//获取文件属性 用于专门判断是否为可执行或普通文件，或其他各种类型文件，返回值为文件字符颜色号码
	int flag;
	if(S_ISLNK(buf.st_mode)){
		flag=32;
	}
	else if(S_ISDIR(buf.st_mode)){
		flag= 33;
	}
	else if(S_ISREG(buf.st_mode)){
		flag=1;
	}
	else if(S_ISCHR(buf.st_mode)){
		flag=35;
	}
	else if(S_ISBLK(buf.st_mode)){
		flag=35;
	}
	else if(S_ISFIFO(buf.st_mode)){
		flag=35;
	}
	else if(S_ISSOCK(buf.st_mode)){
		flag=35;
	}
	if(S_ISREG(buf.st_mode)&&(buf.st_mode&S_IXUSR)){//若文件有可执行属性且为普通文件，则文件为可执行文件
		flag=36;
	}
	return flag;	
}
void my_err(char* err_string,int line){
	fprintf(stderr,"line:%d\n",line);
	perror(err_string);
}
int judge_in_prev_dir(char* filename){//判断文件是否为当前工作目录下的文件
	char filename1[N];
	struct stat buf;
	DIR* dir,* dir1;
	int flag=0;
	char time[N];
	file_node_t* h;
	List_Init(h,file_node_t);
	int count=0;
	struct dirent* ptr,*ptr1;
	if(getcwd(filename1,N)==NULL){//获取本地文件路径
		my_err("getcwd",__LINE__);
		return 0;
	}
	if((dir=opendir(filename1))==NULL){
		my_err("opendir",__LINE__);
		return 0;
}
	while((ptr=(readdir(dir)))!=NULL){//遍历整个目录下的所有文件，找到匹配名字的文件退出循环
		if(strcmp(filename,ptr->d_name)==0){
			flag=1;
			break;
		}
	}
	if(flag==1){
		if((stat(filename,&buf))==-1){//获取文件属性
			perror("stat:");
			return 0;
		}
		if(S_ISDIR(buf.st_mode)){//判断如果是目录的话将，该目录下所有信息按照ls格式打印出来
		
		if(get_all_file_info(h,filename,1)<0){
			my_err("get_info",__LINE__);
			return 0;
			}	
				
			printf("\n");
		}
		else{
			int color;
			color=get_property(buf);
			switch(color){
				case 32:
					printf("\033[32m %-15s\033[0m",filename);
					break;
				case 33:
					printf("\033[33m %-15s\033[0m",filename);
					break;
				case 36:
					printf("\033[36m %-15s\033[0m",filename);
					break;
				case 35:
					printf("\033[35m %-15s\033[0m",filename);
					break;
				case 1:
					printf("%-15s",filename);
					break;
			}
			printf("\n");
		}
	}
	closedir(dir);
	closedir(dir1);
	return flag;
}
int main(int argc ,char ** argv){//1.ls 2.ls -a 3 ls -al 4.ls -a
	//5.ls -R 6.ls dirname 7.ls -l dirname 8.ls -l filename 9.ls -al filename 10.ls -al dirname
	char buf[N];
	char *temp,temp1[N];
	file_node_t*h;
	List_Init(h,file_node_t);
	if(getcwd(buf,N)==NULL){//获取当前工作目录绝对路径，用buf保存
			my_err("getcwd",__LINE__);
		}

	if(argc==1){//判断是否为单纯的ls命令

		if(get_all_file_info(h,buf,1)==0){//根据命令行参数的不同，显示不同格式的信息
				my_err("read",__LINE__);
				exit(1);
			}
		}
	else if(argc==2){//命令行参数为两个时
		temp=argv[1];
		int is;
		if(*(temp)!='-'&&*(temp)!='/'){//判断第二个命令行参数不是以"-"开头且不是绝对路径时,则断定第二个参数为文件名或目录名
			if((is=judge_in_prev_dir(temp))==1){//判断文件是否在当前目录下，如果在，就打印文件信息
				return 1;
			}	
			else if(is==0){//如果文件不存在当前路径下，打印提示信息
				my_err("judge_in_prev_dir",__LINE__);
				printf("file or directory is not exist!\n");
				return 0;
			}
			else{
				printf("查找文件出错或文件不存在!\n");
				return 0;
			}
		}
		else if(*(temp)=='/'){//当第二个参数以绝对路径的形式表示时
			if(get_all_file_info(h,temp,1)==0){//将指定目录包含的文件按照ls+绝对路径  格式打印出来
				my_err("printdir",__LINE__);
				return 0;
			}
		}
		if(*(temp)=='-'){//当第二个参数是'-'结尾时,则第二个后面加命令参数
		
				if(!strcmp(temp,"-a")){
					if((get_all_file_info(h,buf,4))==0){//根据第二个参数的不同传1代表不显示隐藏文件2.代表显示隐藏文件相当于ls -a  3.代表ls -l 4.代表ls -al 命令行为argc为2的情况就是这些。
						my_err("read_dir",__LINE__);
						return 0;
					}
				}
				else if(!strcmp(temp,"-l")){
					if(get_all_file_info(h,buf,3)==0){
						my_err("readdir",__LINE__);
						return 0;
					}
				}
				else if(!strcmp(temp,"-al")){
	
					if(get_all_file_info(h,buf,2)==0){
						my_err("readdir",__LINE__);
						return 0;
						}
					}
				
				else if(!strcmp(temp,"-R")){
					list_by_file(buf,6);
					}
				else if(!strcmp(temp,"-aR")||!strcmp(temp,"-Ra")){
					list_by_file(buf,7);
				}
				
				else if(!strcmp(temp,"-lR")){
					list_by_file(buf,8);
				}
				else if(!strcmp(temp,"-alR")){
					list_by_file(buf,5);
					}				
				}
		}
			else if(argc==3){
			temp=argv[1];
			strcpy(temp1,argv[2]);
			if(!strcmp(temp,"-R")){
				list_by_file(temp1,6);
				}
			if(!strcmp(temp,"-lR")){
				list_by_file(temp1,9);
			}
			}

			else{
				printf("No such command!\n");	
			}
	return 0;
}

