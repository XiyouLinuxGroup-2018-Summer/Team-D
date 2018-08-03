#include<stdio.h>
#include<malloc.h>
extern char **environ;
int main(int argc,char *argv[])
{
    int i;
    printf("命令：\n");
    for(i=0;i<argc;i++)
    {
        printf("argv[%d] is %s",i,argv[i]);
    }
    printf("环境变量：\n");
    for(i=0;environ[i]!=NULL;i++)
        printf("%s\n",environ[i]);
    return 0;
}
