#include<stdio.h>
#include<string.h>
int a[2000];
int b[2000];
int c[2000];
void htime(int t)
{
    int h=0,m=0,s=0;
    if(t>3600)
    {
        h=t/3600;
        t=t%3600;
    }
    if(t>60)
    {
        m=t/60;
        t=t%60;
    }
    if(t>0&&t<60)
    {
        s=t;
    }
    if(8+h<12)
        printf("%02d:%02d:%02d am\n",8+h,m,s);
    else
        printf("%02d:%02d:%02d pm\n",8+h,m,s);
}
int min(int x,int y)
{
    int t;
    t=x<y?x:y;
    return t;
}
int main()
{
	int m,n,i,j,k,t;
    scanf("%d",&m);
	for(i=0;i<m;i++)
	{
        memset(c,0,sizeof(c));
		scanf("%d",&n);
		for(j=1;j<=n;j++)
		{
			scanf("%d",&a[j]);
		}
		for(k=2;k<=n;k++)
		{
			scanf("%d",&b[k]);
		}
        c[0]=0;
        c[1]=a[1];
        for(j=2;j<=n;j++)
        {
            c[j]=min(c[j-2]+b[j],c[j-1]+a[j]);
        }
        t=c[n];
        htime(t);
	}
}
