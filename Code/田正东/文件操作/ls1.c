#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/limits.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <errno.h>
#include <math.h>
#include <fcntl.h>

#define NORMAL 0
#define BLUE    1
#define GREEN  2
#define YELLOW 3
#define WHITE  4

#define PARAM_NONE 0  // 无参数
#define PARAM_A    1  // -a:显示所有文件
#define PARAM_L    2  // -l:一行只显示一个文件的详细信息
#define PARAM_R    4  // -R:连同子目录内容一起列出来
#define MAXROWLEN  80 // 一行显示的最多字符数

int g_leave_len = MAXROWLEN;  //一行剩下的长度，用于输出对齐
int g_maxlen;                 //存放某目录下最长文件名的长度

void display_dir(int flag_param,char *path);

void mycolor(char*name,int color)
{
    if(color==BLUE){
	    printf("\033[;34m %-s\033[0m" "",name);
	}
	else if(color==GREEN){
	    printf("\033[;32m %-s\033[0m" "",name);
	}
	else if(color==NORMAL){
	    printf(" %-s",name);
	}
}

/*错误处理函数，打印出错误所在行数和错误信息*/
void error(const char *p,int line)
{
    fprintf(stderr,"line:%d ",line);
	perror(p);
	exit(1);
}

//获取文件属性并打印
void getprintugrrwx(struct stat a,char *name,int color)
{
    char   time[32];
  	struct passwd *psd; //从该结构体中获取文件所有者的用户名
	struct group  *grp; //从该结构体中获取文件所有者的所属组的组名
	char   b[11]={"----------"};
    
	//获取文件类型
	if(S_ISLNK(a.st_mode))
		b[0]='l';
	if(S_ISREG(a.st_mode))
		b[0]='-';
	if(S_ISDIR(a.st_mode))
		b[0]='d';
	if(S_ISCHR(a.st_mode))
		b[0]='c';
	if(S_ISBLK(a.st_mode))
		b[0]='b';
	if(S_ISFIFO(a.st_mode))
		b[0]='f';
	if(S_ISSOCK(a.st_mode))
		b[0]='s';

	//获取文件所有者权限
	if(a.st_mode & S_IRUSR)
		b[1]='r';
	if(a.st_mode & S_IWUSR)
		b[2]='w';
	if(a.st_mode & S_IXUSR)
		b[3]='x';

	//获取文件所有组权限
	if(a.st_mode & S_IRGRP)
		b[4]='r';
	if(a.st_mode & S_IWGRP)
		b[5]='w';
	if(a.st_mode & S_IXGRP)
		b[6]='x';
	
	//获取其他人权限
	if(a.st_mode & S_IROTH)
		b[7]='r';
	if(a.st_mode & S_IWOTH)
		b[8]='w';
	if(a.st_mode & S_IXOTH)
		b[9]='x';

	//printf("\t");
	//获取用户名，组名
	psd=getpwuid(a.st_uid);
	grp=getgrgid(a.st_gid);

    strcpy(time,ctime(&a.st_mtime));
	time[strlen(time)-1]='\0';    //去掉换行符

	//打印所有
	printf("%s%4ld%-8s%-8s%-6ld%-s",b,a.st_nlink,psd->pw_name,grp->gr_name,a.st_size,time);
	mycolor(name,color);
	printf("\n");
}

//没有用-l时，打印一个文件名并对齐
void printwithoutl(char *name,int color)
{
    int i,len;
	//如果这一行不够打印一个文件名则换行
	if(g_leave_len < g_maxlen){
	    printf("\n");
		g_leave_len = MAXROWLEN;
	}

	len = strlen(name);
	len = g_maxlen - len;
	mycolor(name,color);

	for(i=0;i<len;i++){
	    printf(" ");
	}
	printf(" ");
	//下面的2指示空两格
	g_leave_len -= (g_maxlen + 2);
}

//根据命令行参数和完整路径名显示目标文件
void display(int flag,char *pathname)
{
    int i,j;
	struct stat buf;
	char   name[NAME_MAX + 1];
	int color = NORMAL;

	//从路径中解析出文件名
	for(i=0,j=0;i<strlen(pathname);i++){
	    if(pathname[i]=='/'){
		     j=0;
			 continue;
		}
		name[j++]=pathname[i];
	}
	name[j]='\0';

	//用lstat方便解析连接文件
	if(lstat(pathname,&buf)==-1){
	    if(errno==13){
		    printf("权限有问题\n");
			return ;
		}
		error("stat",__LINE__);
	}

    if(S_ISDIR(buf.st_mode)){
	    color = GREEN;
	}

	if((buf.st_mode & S_IXUSR) && color != GREEN){
	    color = BLUE;
	}

	switch(flag)
    {
        case PARAM_NONE:    //没有任何参数
        case PARAM_R:
            if(name[0]!='.'){
                printwithoutl(name,color);
            }
        break;
        case PARAM_A:       //-a
        case PARAM_A+PARAM_R:
            printwithoutl(name,color);
            break;
        case PARAM_L:
        case PARAM_R+PARAM_L:
            if(name[0]!='.'){   //-l
                getprintugrrwx(buf,name,color);
            }
            break;
        case PARAM_A+PARAM_L:
        case PARAM_A+PARAM_L+PARAM_R:
            getprintugrrwx(buf,name,color);
            break;
        default:
            break;

    }
}

void display_dir(int flag_param,char *path)
{   
    DIR                   *dir;
	struct dirent         *ptr;
    int                   count = 0;
	int                   i,j,len = strlen(path);
	char                  temp[PATH_MAX+1];

	//获取该目录下文件总数和最长的文件名
	dir = opendir(path);
	if(dir == NULL){
	    error("opendir",__LINE__);
	}
	while((ptr = readdir(dir)) != NULL){
	    if(g_maxlen < strlen(ptr->d_name))
			g_maxlen = strlen(ptr->d_name);
		count++;
	}
	closedir(dir);

	char (*file)[PATH_MAX+1]=(char(*)[PATH_MAX+1])malloc(sizeof(char)*count*(PATH_MAX+1));

	//获取该目录下所有的文件名
	dir = opendir(path);
	for(i = 0;i < count; i++){
	    ptr = readdir(dir);
		if( ptr == NULL){
		    error("readdir",__LINE__);
		}
		strncpy(file[i],path,len);
		file[i][len] = '\0';
		strcat(file[i],ptr->d_name);
		file[i][len+strlen(ptr->d_name)] = '\0';
	}

    //使用冒泡法对文件名进行排序，排序后文件名按照字母顺序存储于file
    for(i = 0; i < count-1; i++)
		for(j = 0; j < count-1-i; j++){
		    if( strcmp(file[j],file[j+1]) > 0){
			    strcpy(temp,file[j+1]);
				temp[strlen(file[j+1])] = '\0';
				strcpy(file[j+1],file[j]);
				file[j+1][strlen(file[j])] = '\0';
				strcpy(file[j],temp);
				file[j][strlen(temp)] = '\0';
			}
		}

	if((flag_param & PARAM_R)!=0){
        struct stat buf ;
        char test[30];
        char path_temp[PATH_MAX];
        int strl;
		for(i=0;i<count;i++){
            strcpy(path_temp,file[i]);
            strcpy(test,file[i]+len);
            strl=strlen(file[i]);
            if(test[0]=='.')  
                continue;
           //如果目录文件或目录不存在，报错并退出程序
            if( lstat(path_temp,&buf)== -1 ){
                if(errno==13)
                {
                    printf("没有权限\n");
                    return ;
                }
                error("stat",__LINE__);
            }   
            if( S_ISDIR(buf.st_mode) ){
                path_temp[strl]='/';
                path_temp[strl+1]='\0';
                display_dir(flag_param,path_temp);
            }
    }
}


	if((flag_param & PARAM_R)!=0)
		printf("%s:\n",path);
	for(i = 0; i < count; i++)
		display(flag_param,file[i]);
    
	//如果命令行中没有-l，打印一个换行符
	if((flag_param & PARAM_L)==0)
		printf("\n");

    free(file);
    closedir(dir);

}


int main(int argc , char ** argv)
{
    int i,j,k,num;
    char path[PATH_MAX];
    char param[32];    //保存命令行参数，目录文件名和目录名不在此列
    int  flag_param = PARAM_NONE ;
    struct stat buf ;

    /*命令行参数解析，分析各个选项*/
    j = 0;
    num = 0;
    for(i = 1; i < argc; i++){
        if(argv[i][0] == '-'){
            for(k=1;k < strlen(argv[i]); k++,j++)
                param[j]=argv[i][k];  //将所有的参数都保存到数组中
        num++;//'-'的个数
        }
    }

    /*所支持的参数*/
    for(i=0; i<j; i++)
    {
        if(param[i] == 'a'){
            flag_param |= PARAM_A;
            continue;
        }else if(param[i] == 'l'){
            flag_param |= PARAM_L;
            continue;
        }else if(param[i]=='R'){
            flag_param |= PARAM_R;
            continue;
        }else{
            printf("你输入的这个参数，并没有写嘻嘻嘻...\n");
            exit(1);
        }
    }
    param[j] = '\0';

    //如果没有输入文件名或目录，就显示当前目录
    if((num+1) == argc){
        strcpy(path,"./");
        path[2]='\0';
        display_dir(flag_param,path);
        return 0;
    }

    for(i=1;i<argc;i++)
    {
        //如果不是目录文件名或者目录，解析下一个命令参数
        if(argv[i][0] =='-'){
            continue;
        }
        else{
            strcpy(path,argv[i]);
        }

        //如果目录文件或目录不存在，报错并退出程序
        if( stat(path,&buf)== -1 ){
            error("stat",__LINE__);
        }

        if( S_ISDIR(buf.st_mode) ) //argv[i]是一个目录
            //如果最后一个字符不是'/',就加上'/'
        {
            if(path[strlen(argv[i])-1]!='/'){
                path[strlen(argv[i])]='/';
                path[strlen(argv[i])+1]='\0';
            }
            else{
                path[ strlen(argv[i]) ] = '\0';
            }
            display_dir(flag_param,path);
        }
        else{
            display(flag_param,path);
        }
    }
    return 0;
}

