#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<dirent.h>
#include<erron.h>
#include<grp.h>
#include<psd.h>
#include<stdlib.h>
#define N 256
typedef struct file{
	int fid; // 文件编号
	char filename[128];
	int mode;
// 直接使用整型存储的文件权限(例如 755 存储为 493 也就是 0755)
	int size; // 大小
	char data[256]; // 文件内容
} myfile;
typedef struct node{
	myfile data;
	struct node* prev;
	struct mode* next;
}file_node_t;
int main(){
	int i=1,fd,size;
	char *pathname = "/lib",file_info[N],file_name[N];
	file_node_t* h, *p;
	struct dirent* ptr;
	struct stat buf;
	DIR *dir;
	int mode=0,sum=1;
	struct passwd* psd;
	struct group* grp;
	h=(file_node_t*)malloc(sizeof(file_node_t));
	h->next=h->prev=h;
	if(dir=opendir(pathname)==NULL){
		perror("opendir");
		return 0;
	}
	while((ptr=readdir(dir))!=NULL){
		p=(file_node_t*)malloc(sizeof(file_node_t));
		if(lstat(ptr->d_name,&buf)==-1){
			perror("lstat:");
			return 0;
		}
		strcpy(p->data.filename,ptr->d_name);
		p->data.fid=i;
		if(buf.st_mode&S_IRUSR){
			mode=4;
		}
		if(buf.st_mode&IWUSR){
			mode+=2;
		}
		if(buf.st_mode&IXUSR){
			mode+=1;
		}
		sum=mode*100;
		if(buf.st_mode&S_IRGRP){
			mode=4;
		}
		if(buf.st_mode&S_IWGRP){
			mode+=2;
		}
		if(buf.st_mode&S_IXGRP){
			mode+=1;
		}
		sum+=mode*10;
		if(buf.st_mode&S_IROTH){
			mode=4;
		}
		if(buf.st_mode&S_IWOTH){
			mode+=2;
		}
		if(buf.st_mode&S_I_XOTH){
			mode+=1;
		}
		sum+=mode;
	
		p->data.mode=sum;
		if((fd=open(ptr->name,O_RDWR,S_IRWXU))==-1){
			perror("open:");
			return 0;
		}
		if((size=read(fd,file_info,256))==-1){
			perror("read:");
			return 0;
		}
		*(file_info+strlen(file_info)+1)='\0';
		strcpy(p->data.data,file_info);
		i++;
		p->next=h;
		h->prev->next=p;
		p->prev=h->prev;
		h->prev=p;
	}
	if((fd=open("./allfiles.dat",O_RDWR|O_EXCL|O_TRUNC))==-1){
		perror("open:");
		return 0;
	}
	file_node_t*temp;
	temp=h->next;
	while(temp!=h){//将数据保存在创建的文件中
		if(write(fd,buf))
	}

}
