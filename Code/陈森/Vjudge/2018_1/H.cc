#include <iostream>
#include <string>
#include <cctype>
using namespace std;
int main(void)
{
    string str;
    int num;
    bool flag;
    
    cin >> num;
    getchar();
    while (num--) {
        getline(cin, str);
        flag = true;

        for (auto i : str) {
            if (isalnum(i) || i == '_')
                flag = true;
            else {
                flag = false;
                break;
            }
        }
        if (flag && (isalpha(str[0]) || str[0] == '_'))
            cout << "yes" << endl;
        else
            cout << "no" << endl;
    }    

    return 0;
}
