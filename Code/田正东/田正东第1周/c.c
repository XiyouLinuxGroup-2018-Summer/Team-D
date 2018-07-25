#include <stdio.h>
#include <string.h>
int main()
{
    int N,i,j,b;
    char a[100];
    scanf("%d",&N);
    while(N--)
    {
        scanf("%s",a);
	b=0;
	j=strlen(a)-1;
	while(b<j)
	{  if(a[b]!=a[j])
	   break;
	   b++;
	   j--;
	}
	if(j<=b)
		printf("yes\n");
	else
		printf("no\n");
    }
	return 0;
}
