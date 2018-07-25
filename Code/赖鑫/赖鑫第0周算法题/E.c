#include<stdio.h>
int main()
{
    int a,b,n,N;
    scanf("%d",&N);
    while(N--)
    {
	scanf("%d",&n);
	a=0;
	while(n--)
	{
        scanf("%d",&b);
	a=a+b;
	}
        printf("%d\n",a);
	
    }
}
