/*************************************************************************
	> File Name: show_files.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月25日 星期三 10时50分07秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<dirent.h>
#include<unistd.h>

int my_readir(const char * path)
{
    int k=3;
    DIR * dir;
    struct dirent * ptr;
    if((dir = opendir(path)) == NULL)
    {
        perror("opendir");
        return -1;
    }
    while((ptr = readdir(dir))!=NULL)
    {
        printf("%(%d)s\n",k,ptr->d_name);
    }
    closedir(dir);
    return 0;
}
int main(int argc,char ** argv)
{
    if(argc<2)
    {
        printf("listfile <target path>\n");
        exit(1);
    }
    if(my_readir(argv[1])<0)
    {
        exit(1);
    }
    return 0;
}
