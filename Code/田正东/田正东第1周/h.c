#include<stdio.h>
#include<string.h>
int main()
{
	char a[100];
	int N,b,i;
	scanf("%d ",&N); 
	while(N--)
	{
		int flag=1;
		gets(a);
		b=strlen(a);
		if((a[0]>='a'&&a[0]<='z')||(a[0]>='A'&&a[0]<='Z')||a[0]=='_')
		{
			for(i=0;i<b;i++)
			{
				if(a[i]==' ')
				{
					 flag=0;
					 break;
				}
			}
		if(flag)
		  printf("yes\n");
		else
		  printf("no\n");	
		}
		else
		printf("no\n");
	}
	return 0;
} 
