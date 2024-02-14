#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 10000001
ll datas[MAX];
ll max_len;
ll n, k;
ll ans;
ll t;
ll other = 1;
#define MOD 998244353
inline void input()
{
    scanf("%lld", &n);
    for (ll i = 1; i <= n; i++)
    {
        scanf("%lld", &t);
        datas[t]++;
        if (t > max_len)
        {
            max_len = t;
        }
    }
}
int main()
{
    input();
    for (ll i = 1; i <= max_len; i++)
    {
        for (; other < i * 2 && other <= max_len; other++)
        {
            k += datas[other];
        }
        ans += datas[i] * (datas[i] - 1) * (k - datas[i]) / 2 + datas[i] * (datas[i] - 1) * (datas[i] - 2) / 6;
    }
    printf("%lld", ans % MOD);
}