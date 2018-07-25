#include<stdio.h>
#include<string.h>
int main()
{
    int i,n,j,t;
    char a[55];
    scanf("%d",&n);
    getchar();
    for(i=0;i<n;i++)
    {
        gets(a);
        t=strlen(a);
        if(a[0]>='0'&&a[0]<='9')
        {
            printf("no\n");
        }
        else if(a[0]<'0'||a[0]>'9')
        {
            for(j=0;j<t;j++)
            {
                if(a[j]=='_')
                   continue;
                if(!((a[j]>='0'&&a[j]<='9')||(a[j]>='A'&&a[j]<='Z')||(a[j]>='a'&&a[j]<='z')))
                {
                    printf("no\n");
                    break;
                }
            }
            if(j==t)
            printf("yes\n");
        }
    }
}
