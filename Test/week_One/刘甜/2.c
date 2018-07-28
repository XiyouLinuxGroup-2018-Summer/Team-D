#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int covert(const char *num)
{
    int i,j,t,a,b=1,c=0;
    t=strlen(num);
    for(i=t-1;i>=0;i--)
    {
        a=0;
        a=*(num+i)-'0';
        if(i==t-1)
            a*=b;
        else
        {
            b*=10;
            a*=b;
        }
        c+=a;
    }
    return c;
}
int main()
{
    int f;
    char a[100];
    scanf("%s",a);
    f=covert(a);
    printf("%d\n",f);
}
