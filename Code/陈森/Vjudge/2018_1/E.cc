/*
 * @filename:    E.c
 * @author:      Crow
 * @date:        07/23/2018 09:09:56
 * @description:
 */

#include <cstdio>
#include <iostream>
using namespace std;
int main(void)
{
    char op;
    int a, b, num;

    cin >> num;
    while (num--) {
        cin >> op >> a >> b;
        switch (op) {
            case '+': printf("%d\n",a + b); break;
            case '-': printf("%d\n",a - b); break;
            case '*': printf("%d\n",a * b); break;
            case '/': 
                    if (a % b == 0) {
                        printf("%d\n", a / b);
                        break;
                    }
                    else {
                        printf("%.2f\n", (double)a / b);
                        break;
                    }
            default: break;
        }
    }
}
