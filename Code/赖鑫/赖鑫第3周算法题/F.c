#include<stdio.h>
int min(int a,int b)
{
  if(a>b)
    return b;
  else
    return a;
}
int my_printf(int a)
{

  int hour,minute,second;
  second=a%60;
  minute=((a%3600)-second)/60;
  hour=(8+ (a-second-minute*60)/3600)%24;
  if(hour<12)
  {
    printf("%02d:%02d:%02d am\n",hour,minute,second);
  }
  else
  {
    printf("%02d:%02d:%02d pm\n",hour,minute,second);
  }
}
int main()
{
  int N,n,d,i,j;
  scanf("%d",&N);
  while(N--)
  {
    scanf("%d",&n);
    int k[n];
    int s[n-1];
    int dp[n];
    for(i=0;i<n;i++)
    {
      scanf("%d",&k[i]);
      dp[i]=k[i];
    }

    for(i=0;i<n-1;i++)
    {
      scanf("%d",&s[i]);
    }
    dp[0]=k[0];
    dp[1]=min(s[0],k[0]+k[1]);
    for(i=2;i<n;i++)
    {
      dp[i]=min(dp[i-2]+s[i-1],dp[i-1]+k[i]);
    }
    my_printf(dp[i-1]);
  }
}
