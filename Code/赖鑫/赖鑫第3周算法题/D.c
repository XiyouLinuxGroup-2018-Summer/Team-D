#include<stdio.h>
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
  while(scanf("%d",&n)!=EOF)
  {
    int k[n];
    int dp[n];
    int amax=1;
    for(i=0;i<n;i++)
    {
      scanf("%d",&k[i]);
    }
    for(i=0;i<n;i++)
    {
      dp[i]=1;
      for(j=0;j<i;j++)
      {
        if(k[i]>k[j])
          dp[i]=max(dp[i],dp[j]+1);
      }
      amax=max(amax,dp[i]);
    }
    printf("%d\n",amax);
  }
}
