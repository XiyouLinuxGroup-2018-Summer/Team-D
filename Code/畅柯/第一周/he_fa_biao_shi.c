#include<stdio.h>
#include<stdlib.h>
int VerifiyStr(char* str);
int main(){
	int n,i;
	char str[50];
	scanf("%d",&n);
	while('\n'!=getchar());
	while((scanf("%[^\n]",str))!=EOF){
		while('\n'!=getchar());
		i=VerifiyStr(str);
		if(i==0)printf("no\n");
		else printf("yes\n");
		n--;
		if(n==0)break;
	}
}
int VerifiyStr(char*str){
	int i=0;
	if(*(str+i)<48||*(str+i)>57){
		while(*(str+i)!='\0'){
			if(*(str+i)==' '){
				return 0;
			}
			i++;
		}
		return 1;
	}else{
		return 0;
	}

}
