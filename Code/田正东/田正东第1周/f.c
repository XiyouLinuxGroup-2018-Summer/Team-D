#include <stdio.h>
#include <string.h>
int main()
{
    int N,i,j,b;
	char a[1000];
	scanf("%d",&N);
	while(N--)
	{
	    scanf("%s",a);
		b=0;
		j=strlen(a)-1;
		for(i=0;i<=j;i++)
		{
		   if(a[i]>='0'&&a[i]<='9')
			   b++;
		}
		printf("%d\n",b);
	}
}
