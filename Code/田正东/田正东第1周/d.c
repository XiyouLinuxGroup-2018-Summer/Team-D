#include <stdio.h>
int main()
{
    int a,b,c,d,e;
	while(scanf("%d%d",&a,&b)!=EOF)
	{   
		d=a,e=b;
	    while(b!=0)
		{
		    c=a%b;
			a=b;
			b=c;

		}
		printf("%d\n",d*e/a);
	}
}
