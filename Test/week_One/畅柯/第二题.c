#include<stdio.h>
int convert(char* str);
long e(int num,int k);
int main(){
	int s;
	char *str="-12354";
	s=convert(str);
	printf("%d\n",s);
} 
int convert(char* str)
{
	int i=0,j=0,flag= 0,num= 0,k=0;
	while(*(str+i)!='\0')i++;
	if(*(str+j)=='-'){
		j= 1;
		flag= 1;
	}
	while(1){
			num+=(*(str+i-1)-48)*e(10,k);
			k++;
			i--;
			if(i==j)break;
	}
	return flag==0?num:-num;
}
long e(int num,int k){
	int i=0;
	long s=1;
	for(i=0;i<k;i++){
		s*=10;
	}
	return s;
}
