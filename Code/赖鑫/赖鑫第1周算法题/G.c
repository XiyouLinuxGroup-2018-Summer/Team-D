#include<stdio.h>
#include<string.h>
int main()
{
    int a[100]={0};
    int i,n,m;
    while(1)
    {
	scanf("%d%d",&n,&m);
	if(n==0 && m==0)
		break;
	else
	{
		for(i=0;i<n;i++)
		     scanf("%d",&a[i]);
		for(i=n-1;i>=0;i--)
		{
			if(a[i]>m)
				a[i+1]=a[i];
			else{
				a[i+1]=m;break;}
		}
		for(i=0;i<n;i++)
			printf("%d ",a[i]);
		printf("%d\n",a[i]);
		
	}
    }
}
