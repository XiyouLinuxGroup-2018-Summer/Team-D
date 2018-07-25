#include<stdio.h>
int main()
{
    int a,b,i,j,c,t,k;
    while(scanf("%d%d",&a,&b)!=EOF)
    {
        t=a<b?a:b;
        k=a>b?a:b;
        for(i=1;i<=t;i++)
        {
            j=k*i;
            if(j%t==0)
            {
                break;
            }
        }
        printf("%d\n",j);
    }
}

