#include<stdio.h>
int flag;
void shu(int n,unsigned long long t,int k)
{
    if(flag)
    {
        return;
    }
    if(k==19)
    {
        return;
    }
    if(t%n==0)
    {
        flag=1;
        printf("%lld\n",t);
        //printf("%llu\n",t);
        return;
    }
    shu(n,t*10,k+1);
    shu(n,t*10+1,k+1);
}
int main()
{
    int n;
    while(1)
    {
        scanf("%d",&n);
        if(n==0)
        {
            break;
        }
        flag=0;
        shu(n,1,0);
    }
    return 0;
}

