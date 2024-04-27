#include <bits/stdc++.h>
using namespace std;
int r, l;

int main()
{
    cin >> r >> l;
    int cnt = 0;
    for (int i = r; i <= l; i++)
    {
        int t = i;
        while (t)
        {
            if (t % 10 == 2)
                cnt++;
            t /= 10;
        }
    }
    cout << cnt << endl;
}