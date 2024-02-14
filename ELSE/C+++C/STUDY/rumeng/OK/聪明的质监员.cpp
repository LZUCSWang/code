// https://www.luogu.com.cn/problem/P1314
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 200005
ll n, m, pre_n[MAX], pre_v[MAX], v[MAX], w[MAX], ans, r[MAX], l[MAX], s, sum = 0x3f3f3f3f3f3f3f3f, max_w = -1, min_w = 2147483647;
void init()
{
    ans = 0;
    memset(pre_n, 0, sizeof(pre_n));
    memset(pre_v, 0, sizeof(pre_v));
}
bool judge(ll ww)
{
    init();
    for (ll i = 1; i <= n; i++)
        if (w[i] >= ww)
            pre_n[i] = pre_n[i - 1] + 1, pre_v[i] = pre_v[i - 1] + v[i];
        else
            pre_n[i] = pre_n[i - 1], pre_v[i] = pre_v[i - 1];
    for (ll i = 1; i <= m; i++)
    {
        ans += (pre_n[r[i]] - pre_n[l[i] - 1]) * (pre_v[r[i]] - pre_v[l[i] - 1]);
    }
    sum = min(sum, llabs(ans - s));
    return ans > s;
}
void input()
{
    cin >> n >> m >> s;
    for (ll i = 1; i <= n; i++)
    {
        scanf("%lld%lld", w + i, v + i);
        max_w = max(w[i], max_w);
        min_w = min(w[i], min_w);
    }
    for (int i = 1; i <= m; i++)
    {
        scanf("%lld%lld", l + i, r + i);
    }
}
int main()
{
    input();
    ll left = min_w - 1, right = max_w + 2;
    while (left <= right)
    {
        ll mid = (left + right) >> 1;
        if (judge(mid))
            left = mid + 1;
        else
            right = mid - 1;
    }
    printf("%lld", sum);
}