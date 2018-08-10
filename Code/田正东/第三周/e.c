#include <string.h>
#include <stdio.h>
int n,m,a[110][110],b[110][110],t[4][2]={1,0,-1,0,0,1,0,-1};
int dfs(int x,int y);
int main()
{
    int i,j;
    while(scanf("%d%d",&n,&m) != EOF){
        if(n == -1 && m == -1){
            break;
        }
        if(n < 1 || m > 100){
            continue;
        }
        for(i = 0; i < n; i++){
            for(j = 0; j < n; j++){
                scanf("%d",&a[i][j]);
            }
        }
        printf("%d\n",dfs(0,0));
    }
    return 0;
}

int dfs(int x,int y)
{
    int max = 0,x1,y1,z;
	int i,j;
    if(!b[x][y]){
        for(i = 1; i <= m; i++){
            for(j = 0; j < 4; j++){
				x1 = x + t[j][0] * i;
				y1 = y + t[j][1] * i;
				if(x1 >= 0 && x1 < n && y1 >= 0 && y1 < n && a[x1][y1] > a[x][y]){
					z = dfs(x1,y1);
					if(z > max){
                    max = z;
					}
                }
            }
        }
        b[x][y] = max + a[x][y];
    }
    return b[x][y];
}
