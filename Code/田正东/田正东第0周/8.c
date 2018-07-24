#include <stdio.h>
int main()
{ 
  int a,b,N,d;
  scanf("%d",&a);
  while(a--)
  {	  scanf("%d",&N);
      
       b=0;
        while(N--)
           {    scanf("%d",&d);
               b+=d;}
       printf("%d\n\n",b);
	  
   }
scanf("%d",&N);

 b=0;
  while(N--)
     {    scanf("%d",&d);
         b+=d;}
 printf("%d\n",b);

}
