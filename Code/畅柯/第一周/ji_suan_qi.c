#include<stdio.h>
#include<stdlib.h>
int main()
{
	int n,k,l;
	scanf("%d",&n);
	while('\n'!=getchar());
	int i=0;
	char ch;
	float s;
	while((scanf("%c%d%d",&ch,&k,&l))!=EOF){
		switch(ch){
			case '-':
				s=k-l;
				printf("%.0f\n",s);
				break;
			case '+':
				s=k+l;
				printf("%.0f\n",s);		
				break;
			case '*':
				s=k*l;
				printf("%.0f\n",s);
				break;
			case '/':
				s=k*1.0/l;
				printf("%.2f\n",s);
				break;
			default:	
				printf("Error!\n");
				break;
		}	
		i++;
		while('\n'!=getchar());
		if(i==n)break;
	}
}


