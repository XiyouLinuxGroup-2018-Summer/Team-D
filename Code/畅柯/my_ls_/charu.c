#include<stdio.h>
#include<stdlib.h>
#define N 50
int main(){
	int a[N];
	int m,n,i,temp,j,temp1,flag=0;
	while((scanf("%d%d",&m,&n))!=EOF){
		if(m==0&&n==0)break;
		for(i=0;i<m;i++){
			scanf("%d",&a[i]);
		}
		for(i=0;i<m;i++){
			if(n<a[i]){
				flag=1;
				temp=a[i];
				a[i]=n;
				for(j=i+1;j<m+1;j++){
					temp1=a[j];
					a[j]=temp;
					temp=temp1;		
				}
				break;
			}
			else{
				continue;
			}
		}
	if(flag==0){
		a[m]=n;
	}
	for(i=0;i<m+1;i++){
		printf("%d",a[i]);
		if(i!=m)printf(" ");
		else printf("\n");
		}	
	}
	return 0;
}
