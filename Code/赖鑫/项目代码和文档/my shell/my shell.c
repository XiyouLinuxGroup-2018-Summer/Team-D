#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<dirent.h>
#include <readline/readline.h>
#include <readline/history.h>

void my_printf(char path[100]);
int part(char *buf,char s[100][256]) ;
void explain(char s[100][256],int len);
int find(char *command);

int houtai;       //后台运行符
                   //定义全局变量，用作后面记录特定的运行符都在哪一位，不用再遍历一遍
int out ;          //输出重定向    1
int out_a ;        //输出在文件中追加重定向      2
int in ;           //输入重定向     3
int my_pipe ;      //管道运行符     4

int how;            //用来记录是哪一类的特殊运行符



int main(int argc ,char **argv)
{
    signal( SIGINT,SIG_IGN );
    char *buf=NULL;            //用来保存输入命令的数组
    char s[100][256];         //用来保存分解后的命令的数组
    int len=0,i;               //命令长度，用于判断特殊符号位置
    char path[100];
    char cd[100];
    while(1)
    {
        houtai=0;		//初始化归于0
	    how=0;
        out=0;
	    out_a=0;
        in=0;
        my_pipe=0;
	    buf=(char *)malloc(sizeof(char)*256);
        memset(buf,0,256);         //数组清零
        for(i=0;i<100;i++)
	    {
	        memset(s[i],'\0',256);
	    }

	    if(getcwd(path,100)<0)        //获取当前目录，用于输出显示
        {
		    printf("getcwd出错\n");
            continue;
        }
        my_printf(path);               //命令提示
        buf=readline("\033[35m My Shell :\033[0m ");                //输入命令
	    if( *buf )
        {
            add_history(buf);
        }

        if(strncmp(buf,"cd ",3)==0)		 //cd 命令单独处理
	    {
	        for(i=0;i<strlen(buf);i++)
            {
		        cd[i]=buf[3+i];
            }
	        if(chdir(cd)<0)
	        {
		        printf("目录不存在\n");
	        }
	        continue;
	    }

        if(strcmp(buf,"exit")==0 || strcmp(buf,"logout")==0)   //判断终止条件
        {
            break;
        }
        len=part(buf,s);
        explain(s,len);

    }
}

void my_printf(char path[100])
{
    printf("\033[36m%s \033[0m",path);
    //printf("\033[35m My Shell :\033[0m");
}

int part(char *buf,char s[100][256])
{
    int i=0;
    int len=0;
    int k=0;
    int f=0;
    while(buf[i]!='\0')             //以空格为标记记录个数，保存单个命令
    {
        if(buf[i]==' ' && f==0)
        {
            s[len][k]='\0';
            len++;
            k=0;
            f=1;
        }
        else if (buf[i]!=' ')
        {
            s[len][k++]=buf[i];
            f=0;
        }
        i++;
    }
    s[len][k]=='\0';
    len++;
    return len;
}

void explain(char s[100][256],int len)
{
    int i,j;
    char *arg[len+1];       //字符串指针
    char *argnext[len+1];

    int fd;               //文件参数
    char* file;

    pid_t pid;              //进程参数

    for(i=0;i<len;i++)		//将数组转化为字符串指针
    {
        arg[i]=(char *)s[i];
    }
    arg[i]=NULL;
    int f=0;
    for(i=0;i<len;i++)              //分析各个参数
    {
        if(strcmp(arg[i],"&")==0)      //后台运行符，必须在最后一位
        {
            houtai=1;                   //有的话记为1
            if(i!=(len-1))
            {
                printf("\033[31m 命令错误\n\033[0m");
                break;
            }
            arg[i]=NULL;break;
        }
        if(strcmp(arg[i],">")==0 && arg[i+1]!=NULL)	//输出定向，有的话f记为1,并且用out记录下位置
        {
            how=1;
            f++;
            out=i;
        }
        if(strcmp(arg[i],">>")==0  && arg[i+1]!=NULL)    //输出重定向追加
        {
            how=2;
            f++;
            out_a=i;
        }
        if(strcmp(arg[i],"<")==0 && i!=0)              //输入重定向
        {
            how=3;
            f++;
            in=i;
        }
        if(strcmp(s[i],"|")==0 && i!=0 && arg[i+1]!=NULL)   //管道
        {
            how=4;
            f++;
            my_pipe=i;
        }
    }

    if(f>1)                          //只支持一种
    {
        printf("\033[31m 输入格式错误\n\033[0m");
        return ;
    }
    if(how==1)                    //处理
    {
        file=arg[out+1];
        arg[out]=NULL;
    }
    if(how==2)
    {
        file=arg[out_a+1];
        arg[out_a]=NULL;
    }
    if(how==3)
    {
        file=arg[in+1];
        arg[in]=NULL;
    }
    if(how==4)
    {
        j=0;
        for(i=my_pipe;arg[i]!=NULL;i++)
        {
            argnext[j++]=arg[i+1];
        }
        arg[my_pipe]=NULL;
	    argnext[j]=NULL;
    }
//printf("%d %d \n",my_pipe ,how);
    pid = fork();                    // 创建子进程
    if(pid < 0)
    {
         perror("fork failure");
         return;
    }
    switch(how)
    {
        case 0:                           //case为0时说明只有纯命令
            if(pid==0)			//只在子进程中进行
            {

                if((find(arg[0]))==0)
                {
                    printf("\033[31m %s：找不到命令\n\033[0m",arg[0]);
                    exit(0);
                }
                execvp(arg[0],arg);
                exit(0);
            }
            break;
        case 1:
            if(pid==0)
            {
                if((find(arg[0]))==0)
                {
                    printf("\033[31m %s：找不到命令\n\033[0m",arg[0]);
                    exit(0);
                }
                fd=open(file,O_RDWR|O_CREAT|O_TRUNC,0644);      //以可读可写清空文件方式打开文件
                dup2(fd,1);				//复制文件描述符，重定向标准输出到文件
                execvp(arg[0],arg);
                exit(0);
            }
            break;
        case 2:
            if(pid==0)
            {
                if((find(arg[0]))==0)
                {
                    printf("\033[31m %s：找不到命令\n\033[0m",arg[0]);
                    exit(0);
                }
                fd=open(file,O_RDWR|O_CREAT|O_APPEND,0644);     //以追加方式将数据写入文件尾
                dup2(fd,1);
                execvp(arg[0],arg);
                exit(0);
            }
            break;
        case 3:
            if(pid==0)
            {
                if((find(arg[0]))==0)
                {
                    printf("\033[31m %s：找不到命令\n\033[0m",arg[0]);
                    exit(0);
                }
                fd=open(file,O_RDONLY);       //输入重定向
                dup2(fd,0);
                execvp(arg[0],arg);
                exit(0);
            }
            break;
        case 4:

            if(pid==0)
            {
                pid_t pid2;
                int fd2;

                if((pid2=fork())<0)
                {
                    printf("\033[31m 进程２创建错误\n\033[0m");
                    return;
                }
                if(pid2==0)
                {
                    if((find(arg[0]))==0)
                    {
                        printf("\033[31m %s：找不到命令\n\033[0m",arg[0]);
                        exit(0);
                    }
                    fd2=open("/tmp/newfile",O_WRONLY|O_CREAT|O_TRUNC,0644);
                    dup2(fd2,1);
                    execvp(arg[0],arg);
                    exit(0);
                }
                waitpid(pid2,NULL,0);

                if((find(argnext[0]))==0)
                {
                    printf("\033[31m %s：找不到子命令\n\033[0m",argnext[0]);
                    exit(0);
                }
                fd2=open("/tmp/newfile",O_RDONLY);
                dup2(fd2,0);
                execvp(argnext[0],argnext);
                if(remove("/tmp/newfile"))
                {
                    printf("remove error\n");
                }
                exit(0);
            }
            break;
        default:
            break;
    }

    if(houtai==1)
    {
        printf("\033[32m 进程ＩＤ为：%d\n\033[0m",pid);
        return;
    }
    waitpid(pid, NULL, 0);
}

int find(char *command)
{
    DIR* dp;
    struct dirent* dirp;
    char* path[]={"./","/bin","/usr/bin",NULL};
    if(strncmp(command,"./",2)==0)
    {
        command=command+2;
    }
    int i;
    while(path[i]!=NULL)
    {
        if((dp=opendir(path[i]))==NULL)
        {
            printf("\033[31m 打不开目录\n\033[0m");
        }
        while((dirp=readdir(dp))!=NULL)
        {
            if(strcmp(dirp->d_name,command)==0)
            {
                closedir(dp);
                return 1;
            }
        }
        closedir(dp);
        i++;
    }
    return 0;
}
