/*************************************************************************
	> File Name: beke.c
	> Author: sheng
	> Mail: sheng@163.com 
	> Created Time: 2018-07-27 16:44:40
 ************************************************************************/

#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include <pwd.h>
#include<grp.h>
#include <stdlib.h>
#include<string.h>
#include<time.h>

void my_err(const char *s,int line)
{
    fprintf(stderr,"line:%d",line);
    perror(s);
    exit(1);
}


int main()
{
    char file_name[100]; char time[100];
    int d,u,g,o,i,s;
    int a[3];
    struct passwd *psd;
    struct group *grp;
    struct stat buf;
    printf("请输入正确的文件或目录名称：\n");
	scanf("%s",file_name);

    if(stat(file_name,&buf)==-1)
    {
        my_err("stat",__LINE__);
    }

    if(S_ISLNK(buf.st_mode))
	printf("l");
    else if(S_ISREG(buf.st_mode))
	printf("-");
    else if(S_ISDIR(buf.st_mode))
	printf("d");
    else if(S_ISCHR(buf.st_mode))
	printf("c");
    else if(S_ISBLK(buf.st_mode))
	printf("b");
    else if(S_ISFIFO(buf.st_mode))
	printf("f");
    else if(S_ISSOCK(buf.st_mode))
	printf("s");
  
    s=buf.st_mode;
    o=s%8;
    g=s/8%8;
    u=s/8/8%8;
    a[0]=u;a[1]=g;a[2]=o;
    for(i=0;i<3;i++)
    {
	switch(a[i])
	{
		case 0:printf("---");break;
		case 1:printf("--x");break;
		case 4:printf("r--");break;
		case 2:printf("-w-");break;
		case 3:printf("-wx");break;
		case 5:printf("r-x");break;
		case 6:printf("rw-");break;
		case 7:printf("rwx");break;
	}
}

    psd=getpwuid(buf.st_uid);
    grp=getgrgid(buf.st_gid);

    printf("%4d  ",buf.st_nlink);
    printf("%-8s",psd->pw_name);
    printf("%-8s",grp->gr_name);
    printf("  %6d  ",buf.st_size);

    strcpy(time,ctime(&buf.st_mtime));
    for(i=4;i<16;i++)
 	printf("%c",time[i]);
    printf("  %s\n",file_name);
}
