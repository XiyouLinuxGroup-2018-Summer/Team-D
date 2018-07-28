#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

typedef struct file{
    int fid;     // 文件编号
    char filename[128];
    int mode;     // 直接使用整型存储的文件权限(例如 755 存储为 493 也就是 0755)
    int size;        // 大小
    char data[256];  // 文件内容
} myfile;

int main(int argc,char **argv)
{
    int i=0;
    struct stat buf,buff;
    DIR *dir;
    struct dirent *ptr;
    int b=0;
    int count=0;
    char path[PATH_MAX+1];
    char pathname[300][PATH_MAX+1];
    char filename[300][NAME_MAX+1];
    myfile *p,*q,*head=NULL;
    strcpy(path,"/lib");
    int a=strlen(path);
    if(lstat(path,&buf)==-1)
    {
        perror("lstat");
        exit(1);
    }
    if((dir = opendir(path)) == NULL){
        perror("opendir");
        return -1;
    }
    while((ptr=readdir(dir))!=NULL){
        strcpy(filename[i],ptr->d_name);
        filename[i][strlen(ptr->d_name)]='\0';
        strcpy(pathname[i],path);
        pathname[i][a]='/';
        pathname[i][a+1]='\0'
        strcat(pathname[i],ptr->d_name);
        pathname[i][a+1+strlen(ptr->d_name)]='\0';
        i++;
        count++;
    }
    for(i=0;i<count;i++)
    {
        if(lstat(pathname[i],&buff)==-1)
            perror("lstat49");
        if(!(S_ISDIR(buff.st_mode)))
        {
            p=(myfile *)malloc(sizeof(myfile));
            p->fid=b;
            p->filename=filename[i];
            p->mode=buff.st_mode;
            p->size=buff.st_size;
            p->data
            if(b==0)
            {
                p->next=head;
                head=p;
                q=p;
                b++;
            }
            else
            {
                p->next=NULL;
                q->next=p;
                q=p;
                b++;
            }
        }
    }
}


