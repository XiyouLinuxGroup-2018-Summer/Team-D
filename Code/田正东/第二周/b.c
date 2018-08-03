#include<stdio.h>
#include<string.h>
_Bool book[100010];
struct node{
    int now;
    int step;
}a[100010],next; 
int main()
{
    int n,k,i,j;
	int head = 0,tail = 0;
	a[tail].now = n;
	a[tail].step = 0;
	book[n] = 1;
	tail++;
	int tx;
	while(head < tail)
	{
		for(i=0;i<3;i++)
		{
			if(i == 0)
				next.now = a[head].now - 1;
			if(i == 1)
				next.now = a[head].now + 1;
			if(i == 2)
				next.now = a[head].now * 2;
				next.step = a[head].step + 1;
			if(next.now < 0 || next.now > 100000)
				continue;
			if(book[next.now] == 0)
			{
				book[next.now] = 1;
				a[tail] = next;
				tail++;
			}
			if(next.now == k)
				return next.step;
		}	
		head++;
	}

    while(scanf("%d %d",&n,&k) != EOF){
		if(n > k){
			printf("%d\n",n-k);
		}
		else if( n == k){
			printf("0\n");
		}
		else if(n < k){
			printf("%d\n",next.step);
			}
	}
    return 0;
}
