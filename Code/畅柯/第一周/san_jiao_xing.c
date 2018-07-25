#include<stdio.h>
#include<stdlib.h>
int main(){
	int n,A,B,C;
	scanf("%d",&n);
	while((scanf("%d%d%d",&A,&B,&C))!=EOF){
		if((A+B>C)&&(B+C>A)&&(A+C>B)){
			printf("YES\n");
		}
		else printf("NO\n");
		n--;
		if(n==0)break;
	}
	return 0;
}

