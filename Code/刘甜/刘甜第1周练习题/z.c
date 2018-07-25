#include<stdio.h>
#include<string.h>
int main()
{
    int n,i,j,k,t;
    char a[1000];
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        k=0;
        scanf("%s",a);
        t=strlen(a);
        for(j=0;j<t;j++)
        {
            if(a[j]>='0'&&a[j]<='9')
            {
                k++;
            }
        }
        printf("%d\n",k);
    }
}

