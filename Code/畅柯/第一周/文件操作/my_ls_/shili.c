#include<stdio.h>
int main(){
	int b[3][5]={{1,2,3,3,4},{2,4,5,6,7},{6,7,8,8,6}};
	int * q;
	int (*p)[5];
	for(p=b;p<b+3;p++){
		for(q=*p;q<*p+5;q++)
			printf("%5d",*q);
		printf("\n");
		}
}
