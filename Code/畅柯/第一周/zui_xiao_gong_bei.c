#include<stdio.h>
#include<stdlib.h>
void FindMin(int i,int j);
int main(){
	int i,j;
	while(scanf("%d%d",&i,&j)!=EOF){
		FindMin(i,j);	
	}	
}
void FindMin(int i,int j){
	int max,min,s;
	if(i<j){
		max=j;
		min=i;
	}
	else{
		max=i;
		min=j;		
	}
	if(max%min==0)printf("%d\n",max);
	else{
		for(i=1;i<=min;i++)
		{	
			s=i*max;
			if(s%min==0){
				printf("%d\n",s);
				return ;
			}
		}
	}
}
