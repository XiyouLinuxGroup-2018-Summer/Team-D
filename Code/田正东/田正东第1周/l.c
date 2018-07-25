#include <stdio.h>
#include <string.h>
int main()
{
    char a[100];
	int b,i;
	while(gets(a))
	{
	    b=strlen(a);
		for(i=0;i<b;i++)
		{
		    a[0]=a[0]-32;
			if(a[i]==' ')
			{
			    a[i+1]=a[i+1]-32;
			}
			printf("%c",a[i]);
		}
		printf("\n");
	}
	return 0;
}
