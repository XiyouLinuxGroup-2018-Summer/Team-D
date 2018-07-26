#include<stdio.h>
int main(int argc,char ** argv)
{
    int i;
    for(i=0;i<argc;i++)
       printf("Argument %d is %s.\n",i,argv[i]);
    return 0;
}
/*
结果
Argument 0 is ./hello.
Argument 1 is a.
Argument 2 is b.
Argument 3 is c.
Argument 4 is d.
Argument 5 is e.
*/
