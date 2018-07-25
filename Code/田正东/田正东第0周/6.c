#include <stdio.h>
int main()
{  int a,b,N;
   while(scanf("%d",&N)!=EOF)
   {
       a=0;
        while(N--)
           {    scanf("%d",&b);
               a+=b;}
       printf("%d\n",a);
   }
    return 0;

}
