#include<stdio.h>
struct node
{
    int x;
    int step;
};
int main()
{
    struct node q[100001];
    int a[100001];
    int f;
    int head,tail;
    int m,n,i,x;
    while(scanf("%d%d",&m,&n)!=EOF )
    {
        head=1;
        tail=1;
        for(i=0;i<100000;i++)
		a[i]=0;
        a[100000]=0;
        f=0;
        q[head].x=m;
        q[head].step=0;
        tail++;
        a[m]=1;
        i=0;
        if( m==n)
        {
		printf("0\n");
		continue;
        }
        while(head<tail)
        {
	    x=q[head].x;
	   //printf("%d %d\n",x,q[head].step);
            if(  (x+1)==n  || (x*2)==n ||  (x-1)==n   )
            {
                f=1;
                printf("%d\n",q[head].step+1);
                break;
            }
            if((x*2)<=100000  && (x*2)<(n*2) && a[x*2]==0)
            {
                q[tail].x=x*2;
		q[tail].step=q[head].step+1;
                a[x*2]=1;
                tail++;
            }
	    if((x+1)<=n && a[x+1]==0)
            {
                q[tail].x=x+1;
		q[tail].step=q[head].step+1;
                a[x+1]=1;
                tail++;
            }
	    if((x-1)<=100000   && (x-1)>0 && a[x-1]==0)
            {
                q[tail].x=x-1;
		q[tail].step=q[head].step+1;
                a[x-1]=1;
                tail++;
            }
	
	    head++;

        }
    }
}

