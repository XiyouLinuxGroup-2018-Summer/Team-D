#include <stdio.h>
int main()
{
	int n,i,j,a[1002],m,count[1002];
	while(scanf("%d",&n) != EOF){
		if(n == 0){
			break;
		}
		for(i = 0; i < n; i++){
			scanf("%d",&a[i]);
		}
		m = a[0];
		count[0] = a[0];
		for(i = 1; i < n; i++){
			count[i]=a[i];
            for(j = 0; j < i; j++){
                if(a[j] < a[i] && count[j] + a[i] > count[i]){
                    count[i] = count[j] + a[i];
                }
            }
            if(count[i] > m){ 
				m = count[i];
			}
        }
        printf("%d\n",m);
	}
	return 0;
}
