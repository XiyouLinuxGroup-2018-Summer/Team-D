#include<stdio.h>
#include<stdlib.h>
 
int main()
{	
	int n,m = 1,d = 1,a[1005],b[1005];
	int c = m;
	int e = d + (c-d) / 2;
    while(scanf("%d",&n) != EOF){
		if(n > 1000 || n < 1){
			continue;
		}
        for(int i = 0; i < n; i++){
            scanf("%d",&a[i]);
		}
        b[m] = a[0];
        for(int i = 1; i < n; i++){
            if(a[i] > b[m]){
                b[++m] = a[i];
			}
            else{
                while(d <= c){
				    if(b[e] < a[i]){
				        d = e + 1;
					}
				    else{
				        c = e - 1;
					}
				}
				b[d] = a[i];
            }
        }
        printf("%d\n",m);
    }
    return 0;
}

