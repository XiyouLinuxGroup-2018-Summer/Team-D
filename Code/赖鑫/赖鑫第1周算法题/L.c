#include<stdio.h>
#include<string.h>
int main()
{
    char s[1000];
    int i;
    while(gets(s)!=NULL)
    {
        i=0;
	s[0]=s[0]-32;
        while(s[i]!='\0')
        {
            if(s[i]==' ')
                s[i+1]=s[i+1]-32;
            i++;
        }
        puts(s);
    }
}
