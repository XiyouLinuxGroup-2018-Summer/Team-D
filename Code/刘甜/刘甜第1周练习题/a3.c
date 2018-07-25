#include<stdio.h>
#include<string.h>
int main()
{
    char a[100];
    int i,j,t;
    while(gets(a))
    {
        t=strlen(a);
        a[0]=a[0]-32;
        for(i=1;i<t;i++)
        {
            if(a[i]==' ')
            {
                a[i+1]=a[i+1]-32;
            }
        }
        printf("%s\n",a);
    }
}

