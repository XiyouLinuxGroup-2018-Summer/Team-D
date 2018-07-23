#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
    int N;
    scanf("%d",&N);
    int a[10][10];
    int i=0,j=0;
    int sum[10];
    while(1)
    {
        while(i<N)
        {
            scanf("%d",&a[j][i]);
            sum[j]+=a[j][i];
            i++;
        }

        scanf("%d",&N);
        i=0;
        j++;
        if(N==0)
            break;
    }
    for(i=0;i<j;i++)
    {
         printf("%d\n",sum[i]);
    }
   return 0;
}
