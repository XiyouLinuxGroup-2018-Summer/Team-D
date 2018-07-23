#include<stdio.h>
int main()
{
    int a,b,n;
    while(1)
    {
	scanf("%d",&n);
	if(n==0)
		break;
	else
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
}
