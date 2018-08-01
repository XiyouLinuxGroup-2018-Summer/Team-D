#include<stdio.h>
struct icd{
    int a;
    char b;
    double c;
};
struct idc{
    char a;
    double b;
    int c;
};
int main(){
    printf("%zu  %zu\n",sizeof(struct icd),sizeof(struct idc));
    return 0;
}
