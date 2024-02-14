#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000005
typedef long long ll;
ll n, m, s;
// int query[MAXN][3];
int l[MAXN], r[MAXN];
int w[MAXN], v[MAXN];
ll pn[MAXN], pv[MAXN];
ll sumOfAns;
bool check(int W)
{
    ll Y = 0;
    sumOfAns = 0;
    memset(pn, 0, sizeof(pn));
    memset(pv, 0, sizeof(pv));
    for (int i = 1; i <= n; i++)
    {
        if (w[i] >= W)
        {
            pn[i] = pn[i - 1] + 1;
            pv[i] = pv[i - 1] + v[i];
        }
        else
        {
            pn[i] = pn[i - 1];
            pv[i] = pv[i - 1];
        }
    }
    for (int i = 1; i <= m; i++)
    {
        Y += (pn[r[i]] - pn[l[i] - 1]) * (pv[r[i]] - pv[l[i] - 1]);
    }
    sumOfAns = llabs(Y - s);
    return Y > s;
}
int main()
{
    ios::sync_with_stdio(false);
    cin >> n >> m >> s;
    int mx=-1, mn=2147483647;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d %d", w + i, v + i);
        mx = max(mx, w[i]);
        mn = min(mn, w[i]);
    }
    for (int i = 1; i <= m; i++)
    {
        scanf("%d %d", l + i, r + i);
    }
    int L = mn - 1, R = mx + 2;
    ll ans = 0x3f3f3f3f3f3f3f3f;
    while (L <= R)
    {
        int mid = (L + R) >> 1;
        if (check(mid))
            L = mid + 1;
        else
            R = mid - 1;
        ans = min(ans, sumOfAns);
    }
    cout << ans ;
}