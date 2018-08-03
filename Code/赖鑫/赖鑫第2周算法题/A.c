#include<stdio.h>

void dfs(int x,int y,int step);

int a[5][5];
int b[20][2],min[20][2];
int mins=999,step=0;

void dfs(int x,int y,int step)
{
    int i;
    if(x==4 && y==4)
    {
        if(step<mins)
        {
            mins=step;
            for(i=0;i<step;i++)
            {
                min[i][0]=b[i][0];
                min[i][1]=b[i][1];   
            }
        }
        return;
    }

    if(a[x+1][y]!=1 && (x+1)<=4)
    {
        b[step][0]=x+1;
        b[step][1]=y;
        dfs(x+1,y,step+1);
    }
    if(a[x][y+1]!=1 && (y+1)<=4)
    {
        b[step][0]=x;
        b[step][1]=y+1;
        dfs(x,y+1,step+1);
    }
    if((a[x][y+1]==1  && a[x+1][y]==1) || (x+1)>4 || (y+1)>4 )
    {
       return;
    }

}

int main()
{
    int i,j;
    for(i=0;i<5;i++)
    {
	for(j=0;j<5;j++)
	{
	    scanf("%d",&a[i][j]);
	}
    }
    dfs(0,0,0);
    printf("(0, 0)\n");
    for(i=0;i<mins;i++)
    {
	printf("(%d, %d)\n",min[i][0],min[i][1]);
    }
}

