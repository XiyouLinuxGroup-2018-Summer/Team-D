#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 100
typedef struct tag_unimportant {
char *name;
int num;
} A;
void func(A *a)
{
	strcpy(a->name, "Xiyou Linux Group");
	a->num = 20180728;
}
int main(int argc, char *argv[])
{
	A *a;
	a = (A *)malloc(sizeof(A));
	a->name=(char*)malloc(N);
	func(a);
	printf("%s %d\n", a->name, a->num);
	free(a->name);
	free(a);
	return 0;
}
/*typedef struct tag_unimportant {
    char *name;
    int num;
} A;
void func(A *a)
{
    a = (A *)malloc(sizeof(A));
    strcpy(a->name, "Xiyou Linux Group");
    a->num = 20180728;
}
int main(int argc, char *argv[])
{
    A *a;
    func(a);
    printf("%s %d\n", a->name, a->num);
    return 0;
}

*/
