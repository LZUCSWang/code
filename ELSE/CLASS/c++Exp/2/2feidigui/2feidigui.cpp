//g++ -o 2feidigui 2feidigui.cpp func.cpp
#include <iostream>
#include "func.h"

using namespace std;

int main()
{
    int n, r;
    while (true)
    {
        cout << "Input n and r:";
        cin >> n >> r;
        if (n == 0 && r == 0)
        {
            break;
        }
        if (n < r || n < 1 || r < 1)
        {
            cout << "Input error" << endl;
            continue;
        }
        double result = Cnr(n, r);
        cout << n << " " << r << " " << result << endl;
    }
    return 0;
}
