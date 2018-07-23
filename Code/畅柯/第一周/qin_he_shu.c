#include<stdio.h>
#include<stdlib.h>
#define N 50
void Verified(int i,int j);
int main(){
	int n,i,j;
	scanf("%d",&n);
	while((scanf("%d%d",&i,&j))!=EOF){
		Verified(i,j);
		n--;
	if(n==0)break;
	}
}
void Verified(int i,int j){
	int m,sum1=0,sum2=0;
	int a[N],b[N];
	sum1=1,sum2=1;
	for(m=2;m<=i/2;m++){
		if(i%m==0)sum1+=m;
	}
	for(m=2;m<=j/2;m++){
		if(j%m==0)sum2+=m;
	}
	if(sum1==j&&sum2==i)printf("YES\n");
	else printf("NO\n");
}
