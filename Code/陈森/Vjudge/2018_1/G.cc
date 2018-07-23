#include <vector>
#include <iostream>
using namespace std;
int main(void)
{
    vector<int> vec;
    int m, x, temp;

    while (cin >> m >> x && m != 0 && x != 0) {
        for (auto i = 0; i < m; ++i) {
            cin >> temp;
            vec.push_back(temp);
        }
        auto iter = vec.begin();
        for (; iter != vec.end(); ++iter)
            if (*iter >= x) {
                vec.insert(iter, x);
                break;
            }
        if (iter == vec.end())
            vec.insert(iter, x);
        for (size_t i = 0; i < vec.size() - 1; ++i)
            cout << vec[i] << " ";
        cout << vec[vec.size() - 1] << endl;
        vec.clear();
    }

    return 0;
}
