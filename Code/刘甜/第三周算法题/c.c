#include<stdio.h>
#include<string.h>
int a[1010];
int b[1010];
int main()
{
	int n,i,j,t,m;
	while(1)
	{
		scanf("%d",&n);
		memset(b,0,sizeof(b));
		if(n==0)
		{
			break;
		}
        for(i=0;i<n;i++)
		{
			scanf("%d",&a[i]);
			b[i]=a[i];
		}
		t=0;
	    for(i=1;i<n;i++)
	    {
			m=0;
			for(j=0;j<i;j++)
		    {
				if(a[i]>a[j]&&b[j]>m)
			    {
					m=b[j];
				    b[i]=m+a[i];
			    }
		    }
		}
		t=b[0];
		for(i=1;i<n;i++)
		{
		    if(b[i]>t)
		    {
				t=b[i];
		    }
		}
        printf("%d\n",t);	
	}

}
