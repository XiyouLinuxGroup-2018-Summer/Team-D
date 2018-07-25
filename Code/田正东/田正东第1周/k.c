#include <stdio.h>
#include <math.h>
int main()
{
    int x,y,a,b,i,j,flag;
	while(scanf("%d %d",&x,&y)!=EOF)
	{    
		a=0;
	    if(x==0&&y==0)
		{
		    break;
		}
		for(i=x;i<=y;i++)
		{
		     flag=1;
			 b=i*i+i+41;
			 for(j=2;j<=sqrt(b);j++)
			 {
			     if(b%j==0)
				 {
				     flag=0;
					 break;
				 }
			 }
			 if(flag)
			 {
			     a++;
			 }
		}
		if(a==y-x+1)
		{
		    printf("OK\n");
		}
		else
		{
		    printf("Sorry\n");
		}
	}
	return 0;
}
