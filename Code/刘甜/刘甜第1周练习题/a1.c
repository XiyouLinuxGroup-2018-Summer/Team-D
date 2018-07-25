#include<stdio.h>
int main()
{
    int i,j,m;
    int a,b,t,k;
    scanf("%d",&m);
    for(i=0;i<m;i++)
    {
        t=0;
        k=0;
        scanf("%d%d",&a,&b);
        for(j=1;j<a;j++)
        {
            if(a%j==0)
            {
                t+=j;
            }
        }
        for(j=1;j<b;j++)
        {
            if(b%j==0)
            {
                k+=j;
            }
        }
        if(t==b&&k==a)
        {
            printf("YES\n");
        }
        else
        {
            printf("NO\n");
        }
    }
    return 0;
}
