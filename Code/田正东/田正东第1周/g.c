#include <stdio.h>
int main()
{
    int n,m,a[100],i,j,flag=0;
	while(scanf("%d%d",&n,&m)!=EOF)
	{
	    if(n==0&&m==0)
			break;
		else
		{
		  for(i=0;i<n;i++)
		  {
		    scanf("%d",&a[i]);
		  }
		  for(i=0;i<n;i++)
		  {
		     if(m<a[i])
		   	 {
			    flag=1;
				j=n;
				while(j>i)
				{
				    a[j]=a[j-1];
					j--;
				}
				a[i]=m;
				break;
			 }
		  }
		  if(flag!=1)
            { a[n]=m;}
		  for(i=0;i<n;i++)
		  {printf("%d ",a[i]);}
		  printf("%d\n",a[n]);
		}
	}
	return 0;
}
