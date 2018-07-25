#include<stdio.h>

int main()
{
    int x,y,p;    
    while(scanf("%d%d",&x,&y)!=EOF)
    {
	p=x;
	while(p%y!=0)
	{
		p=p+x;
	}
        printf("%d\n",p);
    }
}
