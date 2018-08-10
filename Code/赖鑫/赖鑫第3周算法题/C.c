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
  while(1)
  {
    scanf("%d",&n);
    if(n==0)
    {
      break;
    }
    int k[n];
    int dp[n];
    int amax=-2147483648;
    for(i=0;i<n;i++)
    {
      scanf("%d",&k[i]);
    }
    for(i=0;i<n;i++)
    {
      dp[i]=k[i];
      for(j=0;j<i;j++)
      {
        if(k[i]>k[j])
          dp[i]=max(dp[i],dp[j]+k[i]);
      }
      amax=max(amax,dp[i]);
    }
    printf("%d\n",amax);
  }
}
