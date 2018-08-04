#include<stdio.h>
char a[110][110];
int n,m,count=0;
int b[8][2]={{0,1},{0,-1},{1,0},{-1,0},{1,1},{-1,1},{1,-1},{-1,-1}};
void cha(int x,int y)
{
    int i;
    int p,q;
    for(i=0;i<8;i++)
    {
        p=x+b[i][0];
        q=y+b[i][1];
        if(p>=0&&p<m&&q>=0&&q<n )
        {    
           if(a[p][q]=='@')
           {
               a[p][q]='!';
               cha(p,q);
           }
        }
    }
    return ;
}

int main()
{
    int i,j;
    while(scanf("%d%d",&m,&n)!=EOF)
    {
        getchar();
        count=0;
        if(m==0&&n==0)
        {
            break;
        }
        for(i=0;i<m;i++)
        {
            scanf("%s",a[i]);
        }

        for(i=0;i<m;i++)
            for(j=0;j<n;j++)
            {
                if(a[i][j]=='@')
                {   
                    count++;
                    a[i][j]='!';
                    cha(i,j);
                }
            }

        printf("%d\n",count);
    }
    return 0;
}
