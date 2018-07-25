#include<stdio.h>
#include<string.h>
int fun(int x)
{
    int i,k=0;
    for(i=1;i<x;i++)
    {
        if(x%i==0)
            k=k+i;
    }
    return k;
}
int main()
{
  int n,x,y;
  scanf("%d",&n);
  while(n--)
  {
      scanf("%d%d",&x,&y);
      if(fun(x)==y && fun(y)==x)
          printf("YES\n");
      else
          printf("NO\n");
  }


}
