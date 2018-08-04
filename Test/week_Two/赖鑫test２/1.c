#include<stdio.h>
int main()
{
    printf("%d\n", & (& 4[(int *)3] )  [5]  );

}
//输出为39，4*4 + 3*1 +5*4

