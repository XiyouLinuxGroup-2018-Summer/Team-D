#include<stdio.h>
int main()
{
   int N;
   int i,a,sum;
   while(scanf("%d",&N)!=EOF)
   {
       sum=0;
       if(N==0)
       {
          break;
       }
       for(i=0;i<N;i++)
       {
          scanf("%d",&a);
          sum+=a;
       }
       printf("%d\n",sum);
   }
}
