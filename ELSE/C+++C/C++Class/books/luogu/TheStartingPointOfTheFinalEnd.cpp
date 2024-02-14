#include <bits/stdc++.h>
using namespace std;
int main()
{
    int datas = 0, b = 1, c = 0, cnt = 1, n, flag[2] = {0, 1};
    cin >> n;
    while (cnt++)
    {
        c = datas % n + b % n;
        datas = b % n;
        b = c % n;
        c = 0;
        if (flag[0] == datas && flag[1] == b)
        {
            cout << cnt - 1 << endl;
            break;
        }
    }
}