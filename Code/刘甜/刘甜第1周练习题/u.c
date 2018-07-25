#include<stdio.h>
int main()
{
    int n,a,b,i,k;
    char t;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        getchar();
        scanf("%c %d %d",&t,&a,&b);
        if(t=='+')
           printf("%d\n",a+b);
        if(t=='-')
           printf("%d\n",a-b);
        if(t=='*')
           printf("%d\n",a*b);
        if(t=='/')
        {
            if(a%b==0)
            {
                printf("%d\n",a/b);
            }
            else
                printf("%.2f\n",a/(b*1.0));
        }
    }
    return 0;
}
