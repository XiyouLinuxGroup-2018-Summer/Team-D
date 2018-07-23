#include <sstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main(void)
{
    string str, temp;
    vector<string> vec;

    while (getline(cin, str)) {
        istringstream is(str);
        while (is >> temp)
            vec.push_back(temp);
        for (auto &i : vec)
            i[0] = i[0] - 32;
        for (size_t i = 0; i < vec.size() - 1; ++i)
            cout << vec[i] << " ";
        cout << vec[vec.size() - 1] << endl;
        vec.clear();
    }

    return 0;
}
