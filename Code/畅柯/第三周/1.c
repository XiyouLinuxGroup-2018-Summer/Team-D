#include<stdio.h>
#include<string.h>

#define N 200
int a[N][N],map[N][N];
int main(){

	int i , j ,l,n,m;
	
	scanf("%d",&n);
	while(n--){
		l = 1;
		scanf("%d",&m);
		memset(a,0,sizeof(a));
		memset(map,0,sizeof(map));
		for(i = 1 ;i<= m ;i++){
			for(j = 1 ; j<= i;j++){
					scanf("%d",&a[i-1][j]);
			}
		}
		map[0][1]=a[0][1];
		for(i = 1 ;i <=m ;i++){
			for(j = 1 ; j<= i+ 1 ;j++){
				printf("a[%d][%d]=%d\n",i,j,a[i][j]);
				map[i][j]= (map[i-1][j]> map[i-1][j-1]? map[i-1][j]:map[i-1][j-1])+a[i][j];
			}
		}
		
		l = map[m-1][0];
		for( i = 1 ;i<= m ;i++){
			l = l<map[m-1][i]? map[m-1][i]:l ; 
		}
		printf("%d\n",l);
	}
	return 0 ;
}
