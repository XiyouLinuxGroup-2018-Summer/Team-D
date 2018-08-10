#include <stdio.h>
int main()
{
	int n,i,j;
	int count[32769];
	count[0] = 1;
	for(i = 1; i <= 3; i++){
		for(j = i; j < 32768; j++){
			count[j] += count[j-i];
		}
	}

	while(scanf("%d",&n) != EOF){
		if(n >= 32768){
			break;
		}
		printf("%d\n",count[n]);
	}
}
