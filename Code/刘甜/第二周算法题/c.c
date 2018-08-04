#include<stdio.h>
#include<stdlib.h>
char a[8][9];
int b[10]={0};
int k,n,count;
void qi(int x,int y)
{
    int i,j;
    if(x==0)
    {
        count++;
    }
    for(i=y;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(a[i][j]=='#'&&b[j]==0)
            {
                b[j]=1;
                if(i<=n-1)
                    qi(x-1,i+1);
                b[j]=0;
            }
        }
    }
}
int main()
{
    int i;
    while(scanf("%d%d",&n,&k)!=EOF)
    {
        count =0;
        if(n==-1&&k==-1)
        {
            break;
        }
        for(i=0;i<n;i++)
        {
            scanf("%s",a[i]);
        }
        qi(k,0);
        printf("%d\n",count);
    }
}

