#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
int main()
{
  FILE *fd;
  char * filename = "test";
  errno = 0;                //错误变量初始化为０
  fd =fopen(filename,"r");
  if(fd=NULL)
  {
    printf("打开文件　%s 失败，错误是　%d\n",filename,errno);
  }
  else
  {
    printf("打开文件 %s 成功\n",filename);
  }
}
