#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct strange {//定义结构体
char a, b, c, d, e, zero;
};
int main(int argc, char *argv[])//主函数和命令行参数
{
	
	struct strange xp[3];//定义结构体数组
	int characters[6] = {'a','b','c','d','e'};//保存字符ascll 码
	for (int i = 0; i < 6; i++) {//定义局部变量i,并执行循环
		*((char *)(xp + 0) + i) = characters[i];//将xp强转为字符数组类型，将characters的每一元素存在xp[0]里面
	}
	strcpy((char *)&xp[1], (char *)characters);
	memcpy(&xp[2], characters, sizeof(struct strange));
	printf("%zu\n", strlen((char *)characters));
	for (int i = 0; i < 3; i++) {
		printf("%c\n", xp[i].e);
	}
}
