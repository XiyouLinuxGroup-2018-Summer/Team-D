#include<stdio.h>
#include<string.h>

//定义结构体
struct strange {
    char a, b, c, d, e, zero;
};

int main(int argc, char *argv[])
{
    struct strange xp[3];          //定义结构体含三个结构体变量的结构体数组,数组名为xp.
    int characters[6] = {'a','b','c','d','e'};  //定义字符数组
    for (int i = 0; i < 6; i++) {
        *((char *)(xp + 0) + i) = characters[i];   //把结构体强制类型转换为字符数组
    }

    strcpy((char *)&xp[1], (char *)characters);  //把characters的字符拷贝到xp[1]中
    memcpy(&xp[2], characters, sizeof(struct strange));  //把 characters中sizeof(struct strange)个字符复制到xp[2]中
    printf("%zu\n", strlen((char *)characters));   //输出characters的长度

    for (int i = 0; i < 3; i++) {
        printf("%c\n", xp[i].e);
    }
}
