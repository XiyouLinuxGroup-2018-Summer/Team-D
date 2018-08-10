#include<stdio.h>
#include<string.h>
int d[35000];
void fun(int n)
{
		int i,j;
		d[0]=1;
		for(i=1;i<=3;i++)
		{
				for(j=i;j<=n;j++)
				{
						d[j]=d[j]+d[j-i];
				}
		}
}
int main()
{
		int n;
		while(scanf("%d",&n)!=EOF)
		{
				memset(d,0,sizeof(d));
				fun(n);
			        printf("%d\n",d[n]);

		}
}
