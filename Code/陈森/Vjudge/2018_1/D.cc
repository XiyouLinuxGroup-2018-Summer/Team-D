#include <iostream>
using namespace std;
int gcd(int a, int b)
{
    return (b == 0) ? a : gcd(b, a % b);
}

int main(void)
{
    int a, b;

    while (cin >> a >> b) {
        int temp = gcd(a, b);
        cout << a / temp * b << endl;
    }

    return 0;
}
