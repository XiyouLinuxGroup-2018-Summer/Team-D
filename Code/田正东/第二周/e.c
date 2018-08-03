#include<stdio.h>
int main()
{
	int a,b,c,d,e,f,num,i,j;
	while(scanf("%d%d%d",&a,&i,&j) != EOF){
		if(a == 0 && i == 0 && j == 0)
			break;
		d = a;
		e = 0;
		f = 0;
		num = 0;
		b = i>j ? i : j;
		c = i<j ? i : j;
		while(1){
			if(d == c && e == b && num > 1){
				printf("NO\n");
				break;
			}
			if(d == e && f == 0){
				printf("%d\n",num);
				break;
			}
			if(f == c){
				d += c;
				f = 0;
				num++;
				continue;
			}
			if(e > 0 && e <= b){
				if(e > c - f){
					e -= c-f;
					f = c;
				}
			else{
					f += e;
					e = 0;
			}
			num++;
			continue;
			}
			else{
				if(d >= b){
					d -= b;
					e = b;
				}
				else{
					d = 0;
					e = d;
				}
				num++;
			}
		}
	}
}



