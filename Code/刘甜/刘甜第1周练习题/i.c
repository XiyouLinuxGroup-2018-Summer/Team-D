#include<stdio.h>
int main()
{
    int i,t,j;
    char a[4];
    while(scanf("%s",a)!=EOF)
    {
        for(i=0;i<3;i++)
        {
            for(j=0;j<2-i;j++)
            {
                if(a[j]>a[j+1])
                {
                    t=a[j+1];
                    a[j+1]=a[j];
                    a[j]=t;
                }
            }
        }
        for(i=0;i<3;i++)
        {
            if(i==0)
               printf("%c",a[i]);
            else
               printf(" %c",a[i]);
        }
        printf("\n");
    }
    return 0;
}
