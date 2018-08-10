#include<stdio.h>
int a[110][110];
int b[110][110];
void fun(int n)
{
		int i,j;
		for(j=1;j<=n;j++)
		{
				b[n][j]=a[n][j];
		}
		for(i=n-1;i>=1;i--)
		{
				for(j=1;j<=i;j++)
				{
						if(b[i+1][j]>b[i+1][j+1])
								b[i][j]=a[i][j]+b[i+1][j];
						else
								b[i][j]=a[i][j]+b[i+1][j+1];
				
				}
		}
}
int main()
{
		int c,n,i,j,k;
		scanf("%d",&c);
		for(k=1;k<=c;k++)
		{
				scanf("%d",&n);
				for(i=1;i<=n;i++)
				{
						for(j=1;j<=i;j++)
						{
								scanf("%d",&a[i][j]);
								b[i][j]=0;
						}
				}
				fun(n);
				printf("%d\n",b[1][1]);

		}
}
