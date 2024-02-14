#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000005
typedef long long ll;
ll a[MAXN];
ll n, m;
// 并查集
ll f[MAXN];
ll find(ll x)
{
    if (f[x] == x)
        return x;
    return f[x] = find(f[x]);
}
void merge(ll x, ll y)
{
    ll fx = find(x);
    ll fy = find(y);
    if (fx != fy)
        f[fx] = fy;
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> n >> m;
    n *= m;
    cin >> m;
    for (int i = 1; i <= n; i++)
    {
        f[i] = i;
    }
    while (m--)
    {
        ll x, y;
        cin >> x >> y;
        merge(x, y);
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++)
    {
        if (find(i) == i)
            ans++;
    }
    // for (in)
    // for (int i = 1; i <= n; i++)
    // {
    //     // if (a[i])
    //     //     ans++;
    //     cout << a[i] << endl;
    // }
    cout << ans << endl;
}