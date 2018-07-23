#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
    int N,M;
    scanf("%d",&M);
    scanf("%d",&N);
    int a[10][10];
    int i=0,j=0;
    int sum[10];
    while(1)
    {
      while(i<N)
      {
        scanf("%d",&a[j][i]);
        sum[j]+=a[j][i];
        i++;
      }
      i=0;
      j++;
      if(j>=M)
          break;
      scanf("%d",&N);
    }
    for(i=0;i<j;i++)
    {
     printf("%d\n",sum[i]);
    }
   return 0;
}
