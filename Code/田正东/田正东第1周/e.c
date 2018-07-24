#include <stdio.h>
int main()
{
    int N,a,b,i=0;
	char c;
	scanf("%d",&N);
	while('\n'!=getchar());
	     while(scanf("%c%d%d",&c,&a,&b)!=EOF)
		 {
		     switch(c)
			 {
				 case '+': printf("%d\n",a+b); break;
				 case '-': printf("%d\n",a-b); break;
				 case '*': printf("%d\n",a*b); break;
				 case '/': 
						   if(a%b==0)
						   {    printf("%d\n",a/b); break;}
						   else
						   {   printf("%.2f\n",(double)a/b); break;}
                 default: break;
			 }
			 i++;
	    	 while('\n'!=getchar());
             if(i==N)
		    	  break;
		 }

}
