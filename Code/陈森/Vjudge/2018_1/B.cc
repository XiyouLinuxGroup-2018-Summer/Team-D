#include <iostream>
#include <cstdio>
using namespace std;
const double PI = 3.1415927;
int main(void)
{
    double radius;

    while (cin >> radius) {
        double V = ((double)4 / 3) * PI * radius * radius * radius;
        printf("%.3lf\n", V);
    }

    return 0;
}
