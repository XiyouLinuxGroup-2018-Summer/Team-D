#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
    int a[30][3];
    int i=0,j=0;
    while(scanf("%d %d",&a[i][0],&a[i][1])!=EOF)
    {
        a[i][2]+=a[i][0]+a[i][1];
        i++;
    }
   for(j=0;j<i;j++)
   {
    printf("%d\n\n",a[j][2]);
   }
   return 0;
}
