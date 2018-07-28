#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct tag_unimportant {
    char *name;
    int num;
} A;
void func(A *a)
{
    a->name = (char *)malloc(sizeof(char)*20);
    strcpy(a->name, "Xiyou Linux Group");
    a->num = 20180728;
}
int main(int argc, char *argv[])
{
    A a;
    func(&a);
    printf("%s %d\n", a.name, a.num);
    free(a.name);
    return 0;
}
/*main函数里只定义了指针变量a，并没有分配存储空间。C语言函数调用是值传递，虽然在func里给形参a分配了空间，但是并不能改变main函数实参a的值，应该
把main函数中的a定义为A的变量，调用函数时对a去地zhi，然后在func中将给a分配空间的语句改为对a的name成员分配20个字节的空间，在return前再加上一条
，释放为a的name分配的空间，结构体变量指向成员用. 指针才用->  */
