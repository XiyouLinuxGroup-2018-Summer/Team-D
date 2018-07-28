#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct tag_unimportant           //定义结构体A，名字和编号
{
    char *name;
    int num;
} A;

                                        
void func(A **a)
{
 
    (*a) = (A *)malloc(sizeof(A));
    						//strcpy((*a)->name, "Xiyou Linux Group");  
						//错误：name是一个字符串指针，没有空间，strcpy函数中是两个字符串的地址，但是直接赋值的话，相当于将字符串“xiyou...”的地址赋给了指针num
    (*a)->name ="Xiyou Linux Group";
    (*a)->num = 20180728;printf("****\n");
}


int main(int argc, char *argv[])
{
    A *a;                                   //结构体指针a传进函数里
    func(&a);					//错误：malloc在函数里给指针分配空间，必须要传二级指针
    printf("%s %d\n", a->name, a->num);
    return 0;
}
