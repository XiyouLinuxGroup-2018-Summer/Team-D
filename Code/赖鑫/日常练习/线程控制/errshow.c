#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>
FILE *open_file(char *filename)
{
  FILE *stream;
  errno=0;
  stream=fopen(filename,"r");
  if(stream==NULL)
  {
    printf("不能打开文件:%s\n,原因是：%s\n",filename,strerror(errno));
    exit(-1);
  }
  else
  {
    return stream;
  }
}
int main()
{
  char *filename = "test1";
  open_file(filename);
  return 0;
}
