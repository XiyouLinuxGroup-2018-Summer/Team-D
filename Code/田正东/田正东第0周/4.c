#include <stdio.h>
int main()
{  int a,b,N;
   while(1)
   {  scanf("%d",&N);
       if(N==0)
	   {   break;}
	   else
	   {   a=0;
	       while(N--)
		   {    scanf("%d",&b);
		       a+=b;}
	    }
	   printf("%d\n",a);
   }
	return 0;

}
