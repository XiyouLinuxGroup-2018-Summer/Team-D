#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
    int N;
    scanf("%d",&N);
    int a[50][50];
    int sum[50];
    int i=0,j=0;
    while(1)
    {
        while(j<N)
        {
            scanf("%d",&a[i][j]);
            sum[i]+=a[i][j];
            j++;
        }
        i++;
        j=0;
        if(scanf("%d",&N)==EOF)
            break;
    }
   for(j=0;j<i;j++)
   {
       printf("%d\n",sum[j]);
   }
   return 0;
}
