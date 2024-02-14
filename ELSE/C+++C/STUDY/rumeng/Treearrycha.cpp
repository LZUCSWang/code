#include <bits/stdc++.h>
using namespace std;
#define MAX 10000001
#define ll long long
ll tree[MAX];
ll n, m;
ll last, now;
void add(ll x, ll k)
{
    for (; x <= n; x += x & -x)
    {
        tree[x] += k;
    }
}
ll query(ll x)
{
    ll ans = 0;
    for (; x; x -= x & -x)
    {
        ans += tree[x];
    }
    return ans;
}
void input()
{
    cin >> n >> m;
    for (ll i = 1; i <= n; i++)
    {
        scanf("%lld", &now);
        add(i, now - last);
        last = now;
    }
}
void main_work()
{
    for (ll i = 1; i <= m; i++)
    {
        ll flag;
        scanf("%lld", &flag);
        if (flag == 1)
        {
            ll l, r, k;
            scanf("%lld%lld%lld", &l, &r, &k);
            add(l, k);
            add(r + 1, -k);
        }
        else
        {
            ll x;
            scanf("%lld", &x);
            printf("%lld\n", query(x));
        }
    }
}
int main()
{
    input();
    main_work();
}