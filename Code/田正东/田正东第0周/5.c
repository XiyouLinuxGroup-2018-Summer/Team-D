#include <stdio.h>
int main()
{   int a,b,N,M;
	scanf("%d",&M);
	while(M--)
    {  scanf("%d",&N);
		if(N==0)
        {   break;}
        else
        {   a=0;
            while(N--)
            {    scanf("%d",&b);
				a+=b;
          }
		}
        printf("%d\n",a);
    }
     return 0; 
 }
