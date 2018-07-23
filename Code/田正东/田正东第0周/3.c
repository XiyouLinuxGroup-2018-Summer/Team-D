#include<stdio.h>
#include<string.h>
#define N 10
int main()
{
    int a[N][3];
    int i=0,j=0;
    while(scanf("%d %d",&a[i][j],&a[i][j+1])!=EOF)
    {
         if(a[i][j]==0&&a[i][j+1]==0)
              break;
         else
              a[i][j+2]=a[i][j]+a[i][j+1];
              i++;
    }
    for(j=0;j<i;j++)
    {
       if(a[j][2]==0)
       {        }
       else
           printf("%d\n",a[j][2]);
    }
    return 0;
}
