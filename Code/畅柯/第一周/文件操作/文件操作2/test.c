#include<stdio.h>
void print(char*temp){
	printf("%s\n",temp);
	return ;
}
int main(int argc,char** argv){
	char *temp;
	temp=argv[1];
	printf("%c\n",*(temp));
	print(temp);
}
