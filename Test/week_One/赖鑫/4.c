#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
//#include<Linux/limits.h>
#include<dirent.h>
#include<grp.h>
#include<pwd.h>
#include<errno.h>
#include<ctype.h>
#include<fcntl.h>

void my_err(const char *s,int line)
{
    fprintf(stderr,"line:%d",line);
    perror(s);
    exit(1);
}
typedef struct file
{
	int fid; // 文件编号
	 char filename[128];
	int mode;
	// 直接使用整型存储的文件权限(例如 755 存储为 493 也就是 0755)
 	int size; // 大小
	char data[256]; // 文件内容
} myfile;
typedef struct data
{
	struct myfile;
	struct data * next;
}data;

int main()
{
	if(chdir("/lib")<0)                        //切换到/lib目录下
        {
		my_err("chdir",__LINE__);
		return 0;
        }
	int fd1;
	if((fd1= open ("allfiles.dat" ,O_CREAT,S_IRUSR|S_IWUSR))==-1)
		{
			my_err("open",__LINE__);
		}
													
	DIR *dir;				//打开目录，获取目录名的同时创建链表
    	struct dirent *ptr;
    	int i=0;
    	dir=opendir("/lib");
	data *p,*q,*head,*t;
	head=(struct data *)malloc(sizeof(struct data));
	head->next=NULL;
    	q=head;
    	while((ptr=readdir(dir))!=NULL)
    	{
                p=(struct data *)malloc(sizeof(struct data));
		strcpy(p->myfile.filename,ptr->d_name);
		
		struct stat buf;
		if(stat(p->myfile.filename,&buf)==-1)
   		{
       			my_err("stat",__LINE__);
   		}
		p->myfile.fid=buf.st_dev;
		p->myfile.mode=buf.st_mode;
		p->myfile.size=buf.st_size;
		int fd;
		if((fd=open(p->myfile.filename,O_RDONLY))==-1)
		{
			my_err("open",__LINE__);
		}
		if((read(fd,p->myfile.data,256))<0)
		{
			my_err("read",__LINE__);
		}
		close(fd);
		if((write(fd1,p->myfile,strlen(p->file) ))!=strlen(p->file))
		{
			my_err("read",__LINE__);
		}
		q->next=p;
        	q=p;
		free(p);
   	}
        closedir(dir);
	close(fd1);
}



