#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdcvbnm,io.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
typedef struct file{
    int fid;
	char filename[128];
	int mode;
	int size;
	char data[256];
}myfile;
void my_err(const char *err_string,int line)
{
    fprintf(stderr,"line:%d ",line);
	perror(err_string);
	exit(1);
}
int my_chmod(int argc,char **argv)
{
    int mode;             //权限
	int mode_u;           //所有者权限
	int mode_g;           //所属组权限
	int mode_o;           //其他用户的权限
	char *path;

	if(argc < 3){
	    printf("%s <mode num> <target file>\n",argv[0]);
		exit(0);
	}

	mode = atoi(argv[1]);
	if(mode > 777 || mode < 0){
	    printf("mode num error!\n");
		exit(0);
	}
	mode_u = mode / 100;
	mode_g = (mode - (mode_u*100)) / 10;
	mode_o = (mode_u * 8 * 8) + (mode_g * 8) + mode_o;
	path = argv[2];

	if( chmod(path,mode) == -1){
	    perror("chmod error");
		exit(1);
	}
//	return 0;
}
int my_open()
{
    int fd;

	if((fd = open("allfiles.dat",O_CREAT | O_EXCL,S_IRUSR | S_IWUSR)) == -1){
	    perror("open");
		exit(1);
	}else{
	    printf("create file success\n");
	}
	close(fd);
	//return 0;
}
int my_read(int fd)
{
    int len;
	int ret;
	int i;
	char read_buf[256]；
	
	if(lseek(fd, 0, SEEK_END) == -1){
	    my_err("lseek",__LINE__);
	}
	if((len = lseek(fd, 0, SEEK_CUR)) == -1){
	    my_err("lseek",__LINE__);
	}
	if((lseek(fd, 0, SEEK_SET)) == -1){
	    my_err("lseek",__LINE__);
	}

	printf("len:%d\n",len);

	if((ret = read(fd, read_buf, len)) < 0){
	    my_err("read",__LINE__);
	}

	for(i=0;i<len;i++){
	    printf("%c",read_buf[i]);
	}
	printf("\n");
	return ret;
}
void list(const char *dirname )
{
    DIR * dir_ptr;
    struct dirent * direntp;
    char *fullpath;
    struct stat info;
    struct file * pHead, *p1;
    FILE *fp;
    int  temp;
	struct stat buf;
	char *out=NULL;
	out=(char *)malloc(PATH_MAX);
        memset(out,0,PATH_MAX);
    pHead=p1=(myfile *)malloc(sizeof(myfile));
    pHead->next=p1->next=NULL;
    p1->fid=1;
	fullpath = (char *)malloc(strlen(dirname)+1+MAXNAMLEN+1);
    while((direntp = readdir( dir_ptr  ))!=NULL)
     {
           myfile *new1 =(myfile *)malloc(sizeof(myfile));
          if(direntp->d_name[0]=='.')
          {
              continue;
          }
          lstat(direntp->d_name,&buf);
          new1->size=buf.st_size;
          new1->mode=buf.st_mode;
          if((buf.st_mode &S_IFMT)==S_IFREG)
          system("cat direntp->d_name >> new1->data");
           sprintf(fullpath,"%s%s",dirname,direntp->d_name);
              strcpy(new1->filename,direntp->d_name);
              i++;
              new1->fid=i;
              p1->next=new1;
                  p1=new1;
              new1->next=NULL;
          }
      myfile * pTemp =pHead ->next;
