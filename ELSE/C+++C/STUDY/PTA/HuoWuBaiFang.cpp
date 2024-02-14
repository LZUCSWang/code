#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000005
typedef long long ll;
// ll a[MAXN];
ll n;
// ll L, W, H;
vector<ll> y;
int main()
{
    ios::sync_with_stdio(false);
    cin >> n;
    int cnt = 0;

    for (int i = 1; i <= sqrt(n); i++)
    {
        if (n % i == 0)
        {
            y.push_back(i);
            if (i * i != n)
                y.push_back(n / i);
        }
    }
    cout << y.size() << endl;
    for (int i = 0; i < y.size(); i++)
    {
        for (int j = 0; j < y.size(); j++)
        {
            for (int k = 0; k < y.size(); k++)
            {
                if (y[i] * y[j] * y[k] == n)
                {
                    cnt++;
                }
            }
        }
    }
    // for (L = 1; L <= n; L++)
    // {
    //     for (W = L; W <= n; W++)
    //     {
    //         if (L * W > n)
    //             break;
    //         if (n % (L * W) == 0)
    //         {
    //             H = n / (L * W);

    //             cnt++;
    //         }
    //     }
    // }
    cout << cnt << endl;
    return 0;
}