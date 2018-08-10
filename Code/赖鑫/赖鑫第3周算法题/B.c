#include<stdio.h>
int main()
{
  int n,i,j,k;
  while(scanf("%d",&n)!=EOF)
  {
    k=0;
    for(i=0;3*i<=n;i++)
    {
      k=k+(n-3*i)/2+1;
    }
    printf("%d\n",k);
  }
}
