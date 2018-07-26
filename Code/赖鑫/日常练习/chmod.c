#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
int main(int argc,char **argv)
{
    int mode,mode_u,mode_g,mode_o;
    if(argc<3)
    {
        printf("格式出错！\n");
        exit(0);
    }
    mode=atoi(argv[1]);
    if(mode>777 || mode<0)
    {
        printf("权限错误！\n");
        exit(0);
    }
    mode_u=mode/100;
    mode_g=mode/10%10;
    mode_o=mode%10;
    mode=(mode_u*8*8)+(mode_g*8)+mode_o;
    if(chmod(argv[2],mode)==-1)
    {
        perror("权限函数错误");
        exit(0);
    }
}
