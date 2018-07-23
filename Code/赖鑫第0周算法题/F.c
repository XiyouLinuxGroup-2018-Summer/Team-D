#include<stdio.h>
int main()
{
    int a,b,n,N;
  
    while(scanf("%d",&n)!=EOF)
    {
	
	a=0;
	while(n--)
	{
        scanf("%d",&b);
	a=a+b;
	}
        printf("%d\n",a);
	
    }
}

