#include<stdio.h>
#include<time.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<errno.h>
#include <stdlib.h>
#include<string.h>
void fun(int s)   //输出权限rwx和类型d/-函数
{
	int d,u,g,o,i;
	o=s%8;
	g=s/8%8;
	u=s/8/8%8;
	d=s/8/8/8/8/8;
	int a[3];
	a[0]=u;a[1]=g;a[2]=o;
	if(d==1)
		printf("-");
	else
		printf("d");
	for(i=0;i<3;i++)
	{
		switch(a[i])
		{
			case 1:printf("--x");break;
			case 4:printf("r--");break;
			case 2:printf("-w-");break;
			case 3:printf("-wx");break;
			case 5:printf("r-x");break;
			case 6:printf("rw-");break;
			case 7:printf("rwx");break;
		}
	}
}
void time1(char s[50])     //输出时间函数
{
	int i;
	char y[4];
	y[0]=s[4];y[1]=s[5];y[2]=s[6];
	if(strcmp(y,"Jan")==0) printf(" 1月 ");
	else if(strcmp(y,"Feb")==0) printf(" 2月 ");
	else if(strcmp(y,"Mar")==0) printf(" 3月 ");
	else if(strcmp(y,"Apr")==0) printf(" 4月 ");
	else if(strcmp(y,"May")==0) printf(" 5月 ");
	else if(strcmp(y,"Jun")==0) printf(" 6月 ");
	else if(strcmp(y,"Jul")==0) printf(" 7月 ");
	else if(strcmp(y,"Aug")==0) printf(" 8月 ");
	else if(strcmp(y,"Sep")==0) printf(" 9月 ");
	else if(strcmp(y,"Oct")==0) printf(" 10月 ");
	else if(strcmp(y,"Nov")==0) printf(" 11月 ");
	else if(strcmp(y,"Dec")==0) printf(" 12月 ");
	for(i=8;i<16;i++)
		printf("%c",s[i]);
}

int main(int argc,char *argv[])
{int a;
    struct stat buf;
    if(argc!=2)
    {
        printf("输入错误：请输入文件\n");
        exit(0);
    }
    if(stat(argv[1],&buf)==-1)
    {
        perror("stat");
        exit(1);
    }
printf("设备编号：%d\n",buf.st_dev);
printf("文件节点编号：%d\n",buf.st_ino);
printf("文件类型和存储权限：%o/n",buf.st_mode);

printf("硬链接数目：%d\n",buf.st_nlink);
printf("用户ID：%d\n",buf.st_uid);
printf("用户组ID：%d\n",buf.st_gid);
printf("设备ID：%d\n",buf.st_rdev);
printf("文件大小：%d\n",buf.st_size);
printf("缓冲区大小：%d\n",buf.st_blksize);
printf("占用文件区块个数：%d\n",buf.st_blocks);
printf("最近一次访问时间：%s\n",ctime(&buf.st_atime));
printf("最后一次被修改时间：%s\n",ctime(&buf.st_mtime));
printf("更新权限时间：%s\n\n",ctime(&buf.st_ctime));
fun(buf.st_mode);
printf("\n");
time1(ctime(&buf.st_mtime));
}
