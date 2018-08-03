#include<stdio.h>
struct node			//定义结构体，里面是三个瓶子还有倒的次数
{
    int s;
    int m;
    int n;
    int step;
};
int main()
{
    struct node q[100000];		//结构体数组．没有必要这么大，可以自己修改
    int m,n,s,head,tail,s1,m1,n1,f;
    while(1)
    {
        scanf("%d%d%d",&s,&m,&n);		//输入s,m,n
        if(s==0 && m==0 && n==0)
            break;
        if(s%2!=0)
        {
            printf("NO\n");
            continue;
        }
        
        int a[101][101][101]={0};	//标记状态是否已经有过的数组
        head=0;
        tail=1;
	f=0;
        q[head].s=s;			//初始的状态
        q[head].m=0;
        q[head].n=0;
        q[head].step=0;
        a[s][0][0]=1;			//初始状态标记
        while(head<tail)
        {
            s1=q[head].s;
            m1=q[head].m;
            n1=q[head].n;
            if( (s1==(s/2) && m1==(s/2) ) || (s1==(s/2) && n1==(s/2) )  || ( m1==(s/2) && n1==(s/2) ) )	//判断结束的条件
            {
                printf("%d\n",q[head].step);
		        f=1;
		        break;
            }				//开始喽
            if(s1>0 && m1<m)		//s-m
            {
                if(s1>(m-m1))
                {
                    q[tail].s=s1-m+m1;
                    q[tail].m=m;
                }
                else
                {
                    q[tail].s=0;
                    q[tail].m=m1+s1;

                }
                q[tail].n=n1;
                if(a[q[tail].s][q[tail].m][q[tail].n]==0)
                {
                    q[tail].step=q[head].step+1;
                    a[q[tail].s][q[tail].m][q[tail].n]=1;
                    tail++;
                }
            }
            if(s1>0 && n1<n)	//s-n
            {
                if(s1>(n-n1))
                {
                    q[tail].s=s1-n+n1;
                    q[tail].n=n;
                }
                else
                {
                    q[tail].s=0;
                    q[tail].n=n1+s1;
                }
                q[tail].m=m1;
                if(a[q[tail].s][q[tail].m][q[tail].n]==0)
                {
                q[tail].step=q[head].step+1;
                a[q[tail].s][q[tail].m][q[tail].n]=1;
                tail++;
                }
            }
            if(s1<s && m1>0)	//m-s
            {
                if(m1>(s-s1))
                {
                    q[tail].m=m1-(s-s1);
                    q[tail].s=s;
                }
                else
                {
                    q[tail].m=0;
                    q[tail].s=m1+s1;
                }
                q[tail].n=n1;
                if(a[q[tail].s][q[tail].m][q[tail].n]==0)
                {
                    q[tail].step=q[head].step+1;
                    a[q[tail].s][q[tail].m][q[tail].n]=1;
                    tail++;
                }
            }
            if(s1<s && n1>0)	//n-s
            {
                if(n1>(s-s1))
                {
                    q[tail].n=n1-(s-s1);
                    q[tail].s=s;
                }
                else
                {
                    q[tail].n=0;
                    q[tail].s=n1+s1;
                }
                q[tail].m=m1;
                if(a[q[tail].s][q[tail].m][q[tail].n]==0)
                {
                    q[tail].step=q[head].step+1;
                    a[q[tail].s][q[tail].m][q[tail].n]=1;
                    tail++;
                }
            }
            if(m1>0 && n1<n)	//m-n
            {
                if(m1>(n-n1))
                {
                    q[tail].m=m1-(n-n1);
                    q[tail].n=n;
                }
                else
                {
                    q[tail].m=0;
                    q[tail].n=n1+m1;
                }
                q[tail].s=s1;
                if(a[q[tail].s][q[tail].m][q[tail].n]==0)
                {
                    q[tail].step=q[head].step+1;
                    a[q[tail].s][q[tail].m][q[tail].n]=1;
                    tail++;
                }
            }
            if(n1>0 && m1<m)	//n-m
            {
                if(n1>(m-m1))
                {
                   q[tail].n=n1-(m-m1);
                   q[tail].m=m;
                }
                else
                {
                    q[tail].n=0;
                    q[tail].m=m1+n1;
                }
                q[tail].s=s1;
                if(a[q[tail].s][q[tail].m][q[tail].n]==0)
                {
                    q[tail].step=q[head].step+1;
                    a[q[tail].s][q[tail].m][q[tail].n]=1;
                    tail++;
                }
            }
            head++;
        }
	if(f==0)
		printf("NO\n");
    }
}
