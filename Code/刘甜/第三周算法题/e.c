#include<stdio.h>
#include<string.h>
int a[110][110];
int b[110][110];
int n,m;
int max(int x,int y)
{
	int t=x>y?x:y;
	return t;
}
int fun(int x,int y)
{
	int i,j;
	if(b[x][y])
	{
		return (b[x][y]);
	}
	b[x][y]=a[x][y];
	for(i=1;i<=m;i++)
	{
		 if(x+i<=n&&a[x+i][y]>a[x][y])
	     {
			 b[x][y]=max(b[x][y],a[x][y]+fun(x+i,y));
	     }
         if(y+i<=n&&a[x][y+i]>a[x][y])
	     {
		     b[x][y]=max(b[x][y],a[x][y]+fun(x,y+i));
	     }
	     if(y-i>=0&&a[x][y-i]>a[x][y])
	     {
		     b[x][y]=max(b[x][y],a[x][y]+fun(x,y-i));
	     }
	     if(x-i>=0&&a[x-i][y]>a[x][y])
	     {   
		     b[x][y]=max(b[x][y],a[x][y]+fun(x-i,y));
	     }
	}
	return (b[x][y]);
}
int main()
{
	int i,j;
	while(1)
	{
		scanf("%d%d",&n,&m);
		memset(b,0,sizeof(b));
		if(n==-1&&m==-1)
		{
			break;
		}
		for(i=1;i<=n;i++)
		{
			for(j=1;j<=n;j++)
			{
				scanf("%d",&a[i][j]);
			}
		}
		printf("%d\n",fun(1,1));
	}
}
