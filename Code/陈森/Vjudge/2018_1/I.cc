#include <iostream>
#include <cmath>
using namespace std;
int main(void)
{
    int num;
    double a, b, c;

    cin >> num;
    while (num--) {
        cin >> a >> b >> c;
        if ((a + b > c) && (a + c > b) && (b + c > a)
            && (fabs(a - b) < c) && (fabs(a - c) < b) && (fabs(b - c) < a))
            cout << "YES" << endl;
        else 
            cout << "NO" << endl;
    }

    return 0;
}
