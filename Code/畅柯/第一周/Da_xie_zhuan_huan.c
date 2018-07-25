/*     输入一个英文句子，将每个单词的第一个字母改成大写字母。
Input
    输入数据包含多个测试实例，每个测试实例是一个长度不超过100的英文句子，占一行。
Output
    请输出按照要求改写后的英文句子。
Sample Input

    i like acm
    i want to get an accepted

Sample Output

    I Like Acm
    I Want To Get An Accepted*/
#include<stdio.h>
#include<stdlib.h>
#define N 100
void ModifyStr(char* str);
int main(){
	char str[N];
	while(scanf("%[^\n]",str)!=EOF){
		while('\n'!=getchar());
		ModifyStr(str);	
	}
}
void ModifyStr(char* str){
	int i=0,flag=0;
	*(str+i)-=32;
	while(*(str+i)!='\0'){
		if(flag==1){
			*(str+i)=*(str+i)-32;
			flag=0;
			i++;
			}
		else{
			if(*(str+i)==' ')flag=1;
			i++;
			}
	}
	printf("%s\n",str);
}
