#include<stdio.h>
#include<stdlib.h>
int main(int argc,char **argv)
{
    if(argc<3)
    {
        printf("输入错误！\n");
        exit(0);
    }

    if(rename(argv[1],argv[2])<0)
    {
        perror("rename");
        exit(1);
    }
}
