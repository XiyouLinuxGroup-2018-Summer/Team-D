#include<stdio.h>
#include<string.h>
char a[100][100];
int dfs(int x,int y);
int main()
{
    int m,n,i,j,k;
    while(1)
    {k=0;
        scanf("%d%d",&m,&n);getchar( );
        if(m==0 && n==0)
	    break;
        for(i=0;i<m;i++)
        {
            scanf("%s",&a[i]);getchar( );
        }
	    for(i=0;i<m;i++)
        {
            for(j=0;j<n;j++)
            {
                if(a[i][j]=='@')
		        {
			    a[i][j]='*';
		            dfs(i,j);
		            k++;
		        }
            }
        }
        printf("%d\n",k);
    }
}
int dfs(int x,int y)
{
    if(a[x+1][y]=='@')
    {
        a[x+1][y]='*';
        dfs(x+1,y);
    }
    if(a[x][y+1]=='@')
    {
        a[x][y+1]='*';
        dfs(x,y+1);
    }
    if(a[x+1][y+1]=='@')
    {
        a[x+1][y+1]='*';
        dfs(x+1,y+1);
    }
    if(a[x-1][y]=='@')
    {
        a[x-1][y]='*';
        dfs(x-1,y);
    }
    if(a[x][y-1]=='@')
    {
        a[x][y-1]='*';
        dfs(x,y-1);
    }
     if(a[x-1][y-1]=='@')
    {
        a[x-1][y-1]='*';
        dfs(x-1,y-1);
    }
    if(a[x-1][y+1]=='@')
    {
        a[x-1][y+1]='*';
        dfs(x-1,y+1);
    }
    if(a[x+1][y-1]=='@')
    {
        a[x+1][y-1]='*';
        dfs(x+1,y-1);
    }
    return 0;
}
