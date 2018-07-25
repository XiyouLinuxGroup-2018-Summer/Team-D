#include <iostream>
#include <cmath>
using namespace std;
bool judge (int val)
{
    bool flag = true;
    for (auto i = 2; i < sqrt(val); ++i)
        if (val % i == 0) {
            flag = false;
            break;
        }
    return (flag == true) ? true : false;
}
int main(void)
{
    int m, n;
    bool flag;

    while (cin >> m >> n) {
        flag = true;
        if (m == 0 && n == 0)
            break;
        for (; m != n; ++m) {
            if (!judge(pow(m, 2) + m + 41)) {
                flag = false;
                break;
            }
        }
        if (flag)
            cout << "OK" << endl;
        else
            cout << "Sorry" << endl;
    }

    return 0;
}
