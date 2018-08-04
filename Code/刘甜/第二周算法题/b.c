#include<stdio.h>
#include<string.h>
struct node
{
    int n;
    int step;
}ji[100010];

int visit[100010];
int sou(int a,int b)
{
    memset(visit,0,100010);
    int head=-1;
    int tail=-1;
    int t,s,i;
    tail++;
    ji[tail].n=a;
    ji[tail].step=0;
    visit[a]=1;
    while(head!=tail)
    {
        head++;
        a=ji[head].n;
        t=ji[head].step;
        s=a+1;
        if(s>0&&s<=100000&&visit[s]==0)
        {
            tail++;
            ji[tail].n=s;
            ji[tail].step=t+1;
            visit[s]=1;
        }
        if(s==b)
            return t+1;
        s=a-1;
        if(s>0&&s<=100000&&visit[s]==0)
        {
            tail++;
            ji[tail].n=s;
            ji[tail].step=t+1;
            visit[s]=1;
        }
        if(s==b)
            return t+1;
        s=a*2;
        if(s>0&&s<=100000&&visit[s]==0)
        {
            tail++;
            ji[tail].n=s;
            ji[tail].step=t+1;
            visit[s]=1;
        }
        if(s==b)
            return t+1;
    }
}

int main()
{
    int a,b;
    while(scanf("%d%d",&a,&b)!=EOF)
    {
        if(a>=b)
        {
            printf("%d\n",a-b);
        }
        else
        {
            printf("%d\n",sou(a,b));
        }
    }
}
