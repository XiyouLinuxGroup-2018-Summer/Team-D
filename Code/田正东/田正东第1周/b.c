#include <stdio.h>
#define PI 3.1415927
int main()
{
  double a;
  while(scanf("%lf",&a)!=EOF)
  {
      printf("%.3f\n",4*PI*a*a*a/3);
  }
  return 0;
}
