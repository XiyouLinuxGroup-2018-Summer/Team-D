#include<stdio.h>
#include <stdlib.h>

struct cx
{
  int n;
  int x;
  int y;
};
int comp(const void*a,const void*b)
{
    return *(int*)a-*(int*)b;
}
int min(int a,int b)
{
  if(a>b)
    return b;
  else
    return a;
}
int max(int a,int b)
{
  if(a>b)
    return a;
  else
    return b;
}

int main()
{
  int i,j,n;
  while(1)
  {
    int n,m,amax,v,w;
    scanf("%d%d",&n,&m);
    if(n==-1 && m==-1)
    {
      break;
    }
    int k[n][n];
    int dp[n][n];
    int a[n],b[n];
    struct cx c[n*n];
    struct cx p;
    v=0;
    for(i=0;i<n;i++)
    {
      for(j=0;j<n;j++)
      {
        scanf("%d",&k[i][j]);
        dp[i][j]=-1;
        c[v].n=k[i][j];
        c[v].x=i;
        c[v].y=j;
        v++;
      }
    }
    amax=k[0][0];
    dp[0][0]=k[0][0];
    qsort(c,n*n,sizeof(struct cx),comp);
    w=0;
    int x,y;
    while(v--)
    {
        x=c[w].x;
        y=c[w].y;
        for(i=max(0,x-m);i<=min(n-1,x+m);i++)
        {

          if(k[x][y]<k[i][y] && i!=x && dp[x][y]!=-1)
          {
            dp[i][y]=max(dp[i][y],k[i][y]+dp[x][y]);
            amax=max(dp[i][y],amax);
          }
        }
        for(i=max(0,y-m);i<=min(n-1,y+m);i++)
        {
          if(k[x][y]<k[x][i]  && i!=y && dp[x][y]!=-1)
          {
            dp[x][i]=max(dp[x][i],k[x][i]+dp[x][y]);
            amax=max(dp[x][i],amax);
          }
        }

      w++;
    }
    printf("%d\n",amax);
  }
}
