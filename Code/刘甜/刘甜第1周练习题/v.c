#include<stdio.h>
int main()
{
    double a,b,c;
    int n,i,k;
    double t1,t2,k1,k2,p1,p2;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%lf%lf%lf",&a,&b,&c);
        t1=a>b?a:b;
        t2=a<b?a:b;
        k1=a>c?a:c;
        k2=a<c?a:c;
        p1=b>c?b:c;
        p2=b<c?b:c;
        if((a+b>c)&&(a+c>b)&&(b+c>a)&&(t1-t2<c)&&(k1-k2<b)&&(p1-p2<a))
        {
            printf("YES\n");
        }
        else
        {
            printf("NO\n");
        }
    }
}
