#include<stdio.h>
#include<string.h>
char s[9][9];
void dfs(int x,int y,int step);
int n,k,v;
int a[9],b[9];
int main()
{
    int i,j,f;
    while(1)
    {   v=0;
        scanf("%d%d",&n,&k);getchar( );
        if(n==-1 && k==-1)
	        break;
        for(i=0;i<n;i++)
        {
            scanf("%s",&s[i]);getchar( );a[i]=0;b[i]=0;
        }
	    dfs(0,0,0);
        printf("%d\n",v);
    }
}
void dfs(int x,int y,int step)
{
    int i,j;
    if(step==k)
    {
        v++;return;
    }
    for(i=x;i<n;i++)
    {
        if(a[i]==1)
            continue;
        for(j=0;j<n;j++)
        {
            if(b[j]==1)
                continue;
            if(s[i][j]=='#')
            {
                a[i]=1;b[j]=1;
                dfs(i+1,j,step+1);
                a[i]=0;b[j]=0;
            }
        }
    }
    return ;
}
