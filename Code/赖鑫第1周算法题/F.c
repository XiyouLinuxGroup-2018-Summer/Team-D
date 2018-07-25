#include<stdio.h>
#include<string.h>
int main()
{
    char s[1000];
    int n,k=0,i;
    scanf("%d",&n);
    while(n--)
    {
	getchar( );
	k=0;
	scanf("%s",s);
	for(i=0;i<strlen(s);i++)
	{
		if(s[i]<='9' && s[i]>='0')
			k++;
	}
	printf("%d\n",k);
    }
}
