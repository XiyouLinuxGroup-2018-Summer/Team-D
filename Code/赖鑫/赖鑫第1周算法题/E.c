#include<stdio.h>
#include<string.h>
int main()
{
    int a,b,n;
    double k;
    char s;
    scanf("%d",&n);
    while(n--)
    {getchar( );
	scanf("%c%d%d",&s,&a,&b);
	
	if(s=='/' && a%b!=0)
		printf("%.2lf\n",(a*1.0)/(b*1.0));
	else if(s=='/' && a%b==0)
		printf("%d\n",a/b);
	else if(s=='+')
		printf("%d\n",a+b);
	else if(s=='-')
		printf("%d\n",a-b);
	else if(s=='*' )
		printf("%d\n",a*b);
	
    }
}
