#include <stdio.h>
int main()
{
    int a,b,n,i,sum;
	scanf("%d",&n);
	while(n--)
	{   
		sum=0;
		scanf("%d%d",&a,&b);
	    for(i=1;i<a;i++)
		{
		    if(a%i==0)
			{
			    sum+=i;
			}
		}
		if(sum==b)
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}
