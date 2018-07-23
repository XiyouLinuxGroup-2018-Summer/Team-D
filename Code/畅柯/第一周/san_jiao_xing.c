#include<stdio.h>
#include<stdlib.h>
int main(){
	int n,a,b,c;
	scanf("%d",&n);
	while((scanf("%d%d%d",&a,&b,&c))!=EOF){
		if(a>0&&b>0&&c>0&&a+b>c&&b+c>a&&a+c>b){
			printf("YES\n");
		}
		else printf("NO\n");
		n--;
		if(n==0)break;
	}
	return 1;
}

