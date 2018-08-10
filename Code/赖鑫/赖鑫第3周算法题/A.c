#include<stdio.h>
int main()
{
  int n,N;
  scanf("%d",&N);
  while(N--)
  {
    scanf("%d",&n);
    int a[n][n];
    int i,j,max;
    for(i=0;i<n;i++)
    {
      for(j=0;j<=i;j++)
      {
        scanf("%d",&a[i][j]);
      }
    }

    for(i=(n-2);i>=0;i--)
    {
      for(j=0;j<=i;j++)
      {
        if(a[i+1][j]>a[i+1][j+1])
        {
          max=a[i+1][j];
        }
        else
        {
          max=a[i+1][j+1];
        }
        a[i][j]=a[i][j]+max;
      }
    }
    printf("%d\n",a[0][0]);
  }
}
