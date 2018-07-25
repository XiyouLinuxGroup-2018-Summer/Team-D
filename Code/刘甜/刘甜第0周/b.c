#include<stdio.h>
#include<stdlib.h>
int main()
{
   int *c;
   int i,a,b,N;
   scanf("%d",&N);
   c=(int *)malloc(sizeof(int *)*N);
   for(i=0;i<N;i++)
   {
      scanf("%d%d",&a,&b);
      c[i]=a+b;
   }
   for(i=0;i<N;i++)
      printf("%d\n",c[i]);
   return 0;
}

