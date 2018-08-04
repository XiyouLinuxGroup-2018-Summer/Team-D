#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct bao
{
    int h[20];
    int z[20];
    int d;
}l[100];
int k=0;
 
void visit(int (*b)[5], int i, int j)
{
    int n, m;
    int p=0;
    l[k].d=0;
	b[i][j] = 2;
	if(i==4&&j==4){
		for(n=0; n<5; n++){
			for(m=0; m<5; m++){
				if(b[n][m] == 2)
                {
                    l[k].h[p]=n;
                    l[k].z[p]=m;
                    p++;
                    l[k].d++;
                }
				else if(b[n][m] == 1)
                    continue;
				else 
                    b[n][m]=0;           
			}	
		}
        k++;
	}
 
	if(b[i-1][j] == 0)
		visit(b, i-1, j);
	if(b[i+1][j] == 0)
		visit(b, i+1, j);
	if(b[i][j-1] == 0)
		visit(b, i, j-1);
	if(b[i][j+1] == 0)
		visit(b, i, j+1);
 
	b[i][j] = 0;
}
int main()
{
    int f;
    int a[5][5];
    int i,j;
    for(i=0;i<5;i++)
    {
        for(j=0;j<5;j++)
        {
            scanf("%d",&a[i][j]);
        }
    }
	visit(a, 0, 0);
    int min=l[0].d;
    f=0;
    for(i=1;i<k;i++)
    {
        if(l[i].d<min)
        {
            min=l[i].d;
            f=i;
        }
        
    }
    for(i=0;i<l[f].d;i++)
    {
        printf("(%d,%d)",l[f].h[i],l[f].z[i]);
        printf("\n");
    }
 
	return 0;
}
