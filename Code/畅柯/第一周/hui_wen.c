#include<stdio.h>
#include<stdlib.h>
#define N 20
int VerifyStr(char*str);
int main(){
	int n,i=0,j=0;
	char str[N];
	scanf("%d",&n);
	int a[N];
	while(i<n){
		scanf("%s",str);
		a[i]=VerifyStr(str);
		i++;
	}
	for(j=0;j<i;j++){
		if(a[j]==0)printf("no\n");
		else printf("yes\n");
	}
}
int VerifyStr(char*str){
	int i=0,k,m=0,flag=0;
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
