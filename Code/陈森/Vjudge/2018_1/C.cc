#include <iostream>
#include <string>
using namespace std;
int main(void)
{
    string str;
    int num, flag;

    cin >> num;
    while (num--) {
        flag = 1;
        cin >> str;
        auto len = str.size();
        for (size_t i = 0, j = len - 1; i <= j; ++i, --j) {
            if (str[i] != str[j]) {
                printf("no\n");
                flag = 0;
                break;
            }
        }
        if (flag)
            printf("yes\n");
    }

    return 0;
}
