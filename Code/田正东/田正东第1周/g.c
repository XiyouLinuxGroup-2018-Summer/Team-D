#include <stdio.h>
int main()
{
    int n,m,a[1000],i;
	while(scanf("%d%d",&n,&m)!=EOF)
	{
	    if(n<0||n>100)
		{continue;}
		else if(n==0&&m==0)
		{break;}
		else
		{
		     for(i=0;i<n;i++)
			 {
			     scanf("%d",&a[i]);
			 }
			 for(i=0;i<n;i++)
			 {
			     if(a[i]<=m)
				 {
				      if(i==(n-1))
					  {
					      printf("%d\n",m);
					  }
					  else
					  {
					      printf("%d ",a[i]);
					  }
				 }
				 if(m<a[i])
				 {
				     printf("%d ",m);
					 for(;i<n;i++)
					 {
					     if(i==(n-1))
						 {
						     printf("%d\n",a[i]);
						 }
						 else
						 {
						     printf("%d ",a[i]);
						 }
					 }
				 }
			 }
		}
	}
	return 0;
}
