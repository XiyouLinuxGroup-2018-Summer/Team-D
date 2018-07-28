#include <stdio.h>
int convert(const char*num)
{
    int a=0;
    const char *ptr=num;
    if(*num=='-'||*num=='+'){
        num++;
    }
    while(*num!='\0')
    {
        if((*num < '0')||(*num > '9')){
            break;
        }
        a = a*10 + (*num - '0');
        num++;
    }
    if(*ptr=='-'){
        a = -a;
    }
    return a;
}

int main()
{
    int num = 0;
    char str[10];
    printf("please input string:");
    gets(str);
    num = convert(str);
    printf("output:%d\n",num);
    return 0;
}

