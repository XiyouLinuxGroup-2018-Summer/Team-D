#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main(void)
{
    vector<char> vec;
    char a, b, c;

    while (cin >> a >> b >> c) {
        vec.push_back(a);
        vec.push_back(b);
        vec.push_back(c);
        sort(vec.begin(), vec.end());
        cout << vec[0] << " " << vec[1] << " " << vec[2] << endl;
        vec.clear();
    }

    return 0;
}
