#include<stdio.h>
#include<stdlib.h>
#define N 20
int VerifyStr(char*str);
int main(){
	int n,i;
	char str[N];
	scanf("%d",&n);
	while('\n'!=getchar());
	while((scanf("%s",str))!=EOF){
		while('\n'!=getchar());
		i=VerifyStr(str);
		if(i==0)printf("no\n");
		else printf("yes\n");
		n--;
		if(n==0)break;
	}
}
int VerifyStr(char*str){
	int i=0,k,m=0;
	while(*(str+i)!='\0')i++;
	k=i/2;
	while(1){
			if(*(str+m)==*(str+i-m-1)){
				m++;
				if(m==k+1)return 1;
			}else{
				return 0;
			}
		}
}
