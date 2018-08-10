#include <stdio.h>
int main()
{
	int c,i,j,n;
	int a[101][101];
	while(scanf("%d",&c) != EOF){
		while(c--){
			scanf("%d",&n);
			for(i = 0; i < n; i++){
				for(j = 0; j <= i; j++){
					scanf("%d",&a[i][j]);
				}
			}
			for(i = n-1; i >= 0; i--){
				for(j = 0; j <= i; j++){
					(a[i][j] + a[i-1][j] > a[i][j+1] + a[i-1][j]) ? (a[i-1][j] = a[i][j] + a[i-1][j]) : (a[i-1][j] = a[i][j+1] + a[i-1][j]);
				}
			}
			printf("%d\n",a[0][0]);
		}
	}
}
