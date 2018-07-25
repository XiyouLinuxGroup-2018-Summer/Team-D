#include<stdio.h>
int main()
{
    int n,i,j,m,t;
    int a[110];
    while(1)
    {
        scanf("%d%d",&n,&m);
        if(n==0&&m==0)
            break;
        for(i=0;i<n;i++)
        {
            scanf("%d",&a[i]);
        }
        if(n==0)
        {
            printf("%d\n",m);
        }
        else
        {
            for(i=0;i<n;i++)
            {
                if(m<=a[i])
                {
                    for(j=n;j>i;j--)
                    {
                        a[j]=a[j-1];
                    }
                    a[i]=m;
                    i=n;
                }
            }
            for(i=0;i<=n;i++)
            {
                if(i==0)
                    printf("%d",a[i]);
                else
                    printf(" %d",a[i]);
            }
            printf("\n");
        }
    }
}
