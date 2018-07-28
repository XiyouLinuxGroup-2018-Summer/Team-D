#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct tag_unimportant {
  char *name;
  int num;
} A;
void func(A *a)
{
  a->name=(char*)malloc(sizeof(char)); // 原因:结构体中的成员name,是一个指向字符串的指针,定义之后要进行初始化,否则为野指针;
  strcpy(a->name, "Xiyou Linux Group");
  a->num = 20180728;
}
int main(int argc, char *argv[])
{
   A *a=(A*)malloc(sizeof(A)); //原因,原代码此处定义了结构体指针,但没有初始化,它的指向,我们不知道,可能指向内存有问题,所以在此进行初始化
   func(a);
   printf("%s %d\n",a->name, a->num);
   return 0;
}
