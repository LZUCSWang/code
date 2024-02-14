#include <bits/stdc++.h>
using namespace std;
#define MAXN 100
typedef long long ll;
ll a[MAXN];
ll n;
int main()
{
    ios::sync_with_stdio(false);
    cin >> n;
    ll t = n;
    int ans = 0, maxans = 0x3f3f3f3f;
    for (int i = 1; i <= n; i++)
    {
        t = n * i;
        while (t)
        {
            if (t % 2)
                ans++;
            t /= 2;
        }
        maxans = min(ans, maxans);
        ans = 0;
    }
    cout << maxans << endl;
}