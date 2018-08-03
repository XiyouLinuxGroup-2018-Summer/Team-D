#include<stdio.h>
int m,f;
unsigned long long n3;

void dfs(unsigned long long n,int step);

int main()
{
    while(1)
    {
        scanf("%d",&m);
        if(m==0)
            break;
        f=0;n3=0;
        dfs(1,1);
        printf("%llu\n",n3);
    }
}

void dfs(unsigned long long  n,int step)
{

    unsigned long long n2;

    if(n%m==0)
    {
        f=1;
 	    n3=n;
        return ;
    }
    if(f==0 && step<19)
    {
        n2=n*10;
        dfs(n2,step+1);
    }
    if(f==0 && step<19)
    {
        n2=n*10+1;
        dfs(n2,step+1);
    } 
    return;

}


