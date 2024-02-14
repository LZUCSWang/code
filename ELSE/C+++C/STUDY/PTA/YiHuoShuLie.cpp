

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    ios::sync_with_stdio(false);
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        int res = 0;
        vector<int> v(32);
        for (int i = 1; i <= n; i++)
        {
            int a;
            cin >> a;
            res ^= a;
            for (int j = 0; j < 32 && a; j++)
            {
                if (a & 1)
                {
                    v[j]++;
                }
                a >>= 1;
            }
        }
        if (res == 0)
        {
            cout << 0 << endl;
        }
        else
        {
            for (int i = 31; i >= 0; i--)
            {
                if (v[i])
                {
                    if (v[i] % 2 == 0)
                        continue;
                    else if (v[i] == 1)
                    {
                        cout << 1 << endl;
                    }
                    else if (n % 2 == 0)
                    {
                        cout << -1 << endl;
                    }
                    else
                    {
                        cout << 1 << endl;
                    }
                    break;
                }
            }
        }
    }
}