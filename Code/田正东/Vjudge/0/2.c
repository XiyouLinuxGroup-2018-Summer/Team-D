#include<stdio.h>
#include<string.h>
int main()
{
    int N;
    scanf("%d",&N);
    int a[10][3];
    int i=0;
    while(i<N)
    {
       scanf("%d %d",&a[i][0],&a[i][1]);
        a[i][2]=a[i][0]+a[i][1];
        i++;
    }
    for(i=0;i<N;i++)
    {
        printf("%d\n",a[i][2]);
    }
    return 0;
}
