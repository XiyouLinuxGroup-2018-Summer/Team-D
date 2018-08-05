#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 10
void search(int x, int y);
int columns[N];
int num , fang_an ,area;
char qipan[N][N];
int main(){
		
	int j,i ;
	while((scanf("%d%d",&area,&num))!=EOF){
		while('\n'!=getchar());
		if(area == -1 && num==-1 )break;
		memset(qipan, 0 , sizeof(qipan)); 
		
		for(i = 0; i < area ;i++  ){
				scanf("%s",qipan[i]);
				while('\n'!=getchar());
		}

		fang_an = 0;

		memset(columns,0,sizeof(columns));
	
		search(0 ,0);
		printf("%d\n",fang_an);	
	}
	
}
void search(int x ,int y){ 
	int i,j;

	if(y == num ){
	
		fang_an++ ;
		return ;
	}
	for( i = x ; i< area ; i++){
		
		for( j = 0 ;j< area ; j++){
		
			if((!columns[j]) && qipan[i][j] == '#'){
			
				columns[j] = 1;
			
				search(x+1,y+1);
				
				columns[j] = 0;	
			}	
			
		}
	}
	return ; 
}
