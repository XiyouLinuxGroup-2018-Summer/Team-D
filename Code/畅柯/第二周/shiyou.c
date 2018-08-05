#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 20
int row ,column ;
char map[N][N];
int go_map(int x,int y);
int s[2][8]={{-1,0,1,1,1,0,-1,-1},{-1,-1,-1,0,1,1,1,0}};
int main(){
	
	int i, j,num;
	while(scanf("%d%d",&row,&column)!=EOF){
		if(row==0&&column==0)break;
		while('\n' != getchar());
		num = 0;
		memset(map,0,sizeof(map));
		for(i = 0 ; i<row ;i++){
			scanf("%s",map[i]);
		}
	
		for(i=0;i<row;i++){
			
			for(j=0;j<column;j++){
				
				if(map[i][j]=='@'){
				
					num ++;
					go_map(i,j);	
				}
			}
		}
		printf("%d\n",num);	
	}
}
int go_map(int x,int y){
	
	map[x][y]='*';
	int a ,b, i;
	for(i=0;i<8;i++){
		
		a = x+ s[0][i];
		b = y +s[1][i];
		if(map[a][b] =='@'){
				
			go_map(a,b);
		}
	}
	return 1;
}
