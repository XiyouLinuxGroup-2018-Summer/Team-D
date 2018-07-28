#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct strange {                             //定义一个结构体，里面是6个字符的定义
    char a, b, c, d, e, zero;
};

int main(int argc, char *argv[])
{
    struct strange xp[3];			//定义结构体数组
    int characters[6] = {'a','b','c','d','e'};                 //定义数组   
    for (int i = 0; i < 6; i++) {
        *(   (char *)(xp + 0)  + i) = characters[i];     //将结构体数组中的第一个结构体强制转换为结构体指针，给该结构体中的第i个区域赋值
    }

    strcpy((char *)&xp[1], (char *)characters);       //将数组前者赋给后者名转换为char指针型，将第二个及结构体首地址的地址也转换，然后
    memcpy(&xp[2], characters, sizeof(struct strange));  //将第三个结构体数组用
    printf("%zu\n", strlen( (char *) characters));        //

    for (int i = 0; i < 3; i++) {
        printf("%c\n", xp[i].e);
    }
}
