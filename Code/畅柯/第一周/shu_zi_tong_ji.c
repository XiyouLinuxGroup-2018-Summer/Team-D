#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define N 50
int main(){
	int n,i,k,j=0;
	char str[N];
	scanf("%d",&n);
	while('\n'!=getchar());
	while((scanf("%s",str))!=EOF){
		k=0;
		for(i=0;i<strlen(str);i++){
			if(str[i]>=48&&str[i]<=57){
				k++;
			}
		}
		printf("%d\n",k);
		while('\n'!=getchar());
		j++;
		if(j==n)break;
	}
}
