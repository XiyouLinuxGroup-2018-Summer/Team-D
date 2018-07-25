#include <iostream>
#include <vector>
using namespace std;
int main(void)
{
    int a, b, num;
    int resa, resb;
    vector<int> veca;
    vector<int> vecb;

    cin >> num;
    while (num--) {
        cin >> a >> b;
        resa = 0;
        resb = 0;
        for (auto i = 1; i < a; ++i)
            if (a % i == 0)
                veca.push_back(i);
        for (auto i = 1; i < b; ++i)
            if (b % i == 0)
                vecb.push_back(i);
        
        for (auto i : veca)
            resa += i;
        for (auto i : vecb)
            resb += i;
        if (resa == b && resb == a)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
        veca.clear();
        vecb.clear();
    }

    return 0;
}
