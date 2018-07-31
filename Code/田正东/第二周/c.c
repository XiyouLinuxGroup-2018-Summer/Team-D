#include<stdio.h>
#include<string.h>
char a[10][10];
int col[11];
int n,k,count;
void dfs(int i,int k)
{
    int j;
    if(i > n + 1)  
		return;
    if(k == 0)
    {
        count++;
        return ;
    }
    for(j = 0; j < n; j++)
    {
        if(a[i][j] == '#' && !col[j])
        {
            col[j] = 1;
            dfs(i+1,k-1);
            col[j] = 0;
        }
    }
    dfs(i+1,k);
}

int main()
{
	int i,j;
	while(scanf("%d %d",&n,&k) != EOF)
	{
		if(n == -1 && k == -1)  
			break;
		count=0;
		for(i = 1; i <= n; i++)
		{
			scanf("%s",a[i]);
		}
		dfs(1,k);
		
		printf("%d\n",count);
	} 
	return 0;
} 
