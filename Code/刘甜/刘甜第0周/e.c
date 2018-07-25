#include<stdio.h>
int main()
{
   int N,M;
   int i,j,a,sum;
   scanf("%d",&N);
   for(j=0;j<N;j++)
   {
       scanf("%d",&M);
       sum=0;
       for(i=0;i<M;i++)
       {
          scanf("%d",&a);
          sum+=a;
       }
       printf("%d\n",sum);
   }
}

