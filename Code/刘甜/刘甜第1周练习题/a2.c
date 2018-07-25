#include<stdio.h>
int su(int n)
{
    int i;
    for(i=2;i<n;i++)
    {
        if(n%i==0)
        {
            return 0;
        }
    }
    return 1;
}
int fun(int m)
{
    int f;
    f=m*m+m+41;
    return f;
}
int main()
{
    int x,y,t,i;
    while(1)
    {
        scanf("%d%d",&x,&y);
        if(x==0&&y==0)
        {
            break;
        }
        else
        {
            for(i=x;i<=y;i++)
            {
                t=fun(i);
                if(!su(t))
                {
                   break; 
                }
            }
            if(i>y)
              printf("OK\n");
            else
               printf("Sorry\n");
        }
    }
    return 0;
}

