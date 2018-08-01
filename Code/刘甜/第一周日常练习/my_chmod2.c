#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/stat.h>
#include<unistd.h>
#include<sys/types.h>
#include<errno.h>

int main(int argc,char *argv[])
{
    struct stat buf;
    //检查参数个数
    if (argc != 2)
    {
        printf("Usage: my_stat <filename>\n");
        exit (0);
    }
    //获取文件属性
    if( stat(argv[1],&buf) == -1 )
    {
        perror("stat:");
        exit(1);
    }

    //打印出文件属性
    printf("device is: %ld\n", (long)buf.st_dev);
    printf("inode is: %ld\n",(long) buf.st_ino);
    printf("mode is: %o\n", buf.st_mode);
    printf("number of hard links is: %ld\n", (long)buf.st_nlink);
    printf("user ID of owner is: %ld\n", (long)buf.st_uid);
    printf("group ID of owner is: %ld\n",(long)buf.st_gid);
    printf("device type (if inode device) is: %ld\n",(long) buf.st_rdev);

    printf("total size, in bytes is: %ld\n", (long)buf.st_size);
    printf("blocksize for filesysem I/O is: %ld\n",(long) buf.st_blksize);
    printf("number of blocks allocated is: %ld\n", (long)buf.st_blocks);

    printf("time of last access is: %s", ctime(&buf.st_atime));
    printf("time of last modification is: %s",ctime(&buf.st_mtime));
    printf("time of last chang is: %s", ctime(&buf.st_ctime));

    return 0;
}
