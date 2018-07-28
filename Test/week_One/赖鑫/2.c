#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int convert(const char *num)
{
    int i,d=0;
    for(i=0;i<strlen(num);i++)
    {
	if(num[i]>='0' && num[i]<='9')
	{
	    d=d*10+(num[i]-'0');
	}
    }
    return d;
}


int main()
{
    char s[20];
    int d;
    scanf("%s",s);
    d=convert(s);
    printf("%d\n",d);
}
