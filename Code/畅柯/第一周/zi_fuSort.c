#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define N 20
void Sort(char*str);
int main(){
	char str[N];
	int i=0;
	while((scanf("%s",str))!=EOF){
		Sort(str);
		while(*(str+i)!='\0'){
			printf("%c",*(str+i));
			if(*(str+1+i)!='\0')printf(" ");
			else printf("\n");
				i++;
		}
		i=0;
		*(str+i)='\0';
	}
	return 0;
}
void Sort(char*str){
	int i=0,j,k;
	while(*(str+i)!='\0')i++;
	for(j=0;j<i;j++){
		char ch;
		for(k=0;k<i-j-1;k++){
			if(*(str+k)>*(str+k+1)){
				ch=*(str+k);
				*(str+k)=*(str+k+1);
				*(str+k+1)=ch;
			}
		}
	}
}
