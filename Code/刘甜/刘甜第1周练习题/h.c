#include<stdio.h>
#include<string.h>
int main()
{
    int n,i,j,k,t;
    char a[1000];
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%s",a);
        t=strlen(a);
        j=0;
        k=t-1;
        while(j<=k)
        {
            if(a[k]!=a[j])
            {
                break;
            }
            k--;
            j++;
        }
        if(j>k)
        {
            printf("yes\n");
        }
        else
        {
            printf("no\n");
        }
    }
    return 0
}
