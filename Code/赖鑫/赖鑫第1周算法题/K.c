#include<stdio.h>
#include<string.h>
int fun(int n)
{
    int i,f=0;
    for(i=2;i<n;i++)
    {
        if(n%i==0)
        {
            f=1;break;
        }
    }
    return f;
}
int main()
{
    int x,y,i,n;
    while(1)
    {
        scanf("%d%d",&x,&y);
        if(x==0 && y==0)
            break;
        else
        {
            for(i=x;i<=y;i++)
            {
                n=i*i+i+41;
                if(fun(n)==1)
                {
                    printf("Sorry\n");break;
                }
            }
            if(fun(n)==0)
                printf("OK\n");
        }
    }
}
