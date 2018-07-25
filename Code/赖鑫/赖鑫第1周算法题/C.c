#include<stdio.h>
#include<string.h>
int main()
{
    int n,i,k=0;
    char a[1000],b[1000];
    scanf("%d",&n);
    while(n--)
    {k=0;
	scanf("%s",a);
	for(i=strlen(a)-1;i>=0;i--)
	{
		b[k++]=a[i];
	}
	b[k]='\0';
	if(strcmp(a,b)==0)
		printf("yes\n");
	else
		printf("no\n");
    }

}
