#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 1e9
#define MAX 10
#define ll long long
// 7 4 10
// 2 6
// 5 -3
// 10 3
// 11 -3
// 13 1
// 17 6
// 20 2
ll n, d, k, x[MAX], s[MAX], dp[MAX];
bool check(ll last, ll now, ll g)
{
    if (d <= g)
    {
        if (x[now] - x[last] >= 1 && x[now] - x[last] <= d + g)
            return true;
    }
    else if (x[now] - x[last] >= d - g && x[now] - x[last] <= d + g)
        return true;
    return false;
}
ll ans;
bool vis[MAX];
deque<ll> q;
bool maxslidingwindow(ll g)
{
    long long left = 0, right = 0;
    memset(dp, -0x3f3f3f, sizeof(dp));
    dp[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        while (x[i] - x[right] > max(d - g, 1ll))
        {
            right++;
            while (!q.empty() && dp[right] >= dp[q.back()])
                q.pop_back();
        }
        while (x[i] - x[left] > d + g)
        {
            left++;
            q.pop_front();
        }
        q.push_back(right);
        dp[i] = s[i] + dp[q.back()];
        if (dp[i] >= k)
        {
            ans = min(ans, g);
            return true;
        }
    }
    return false;
}
bool judge(ll g)
{
    memset(dp, -0x3f3f3f, sizeof(dp));
    memset(vis, 0, sizeof(vis));
    dp[0] = 0;
    vis[0] = true;
    for (ll i = 1; i <= n; i++)
        for (ll j = i - 1; j >= 0; j--)
        {
            if (x[i] - x[j] > d + g)
                break;
            if (x[i] - x[j] < max(1ll, d - g))
                continue;
            if (check(j, i, g) && vis[j])
            {
                vis[i] = true;
                dp[i] = max(dp[i], dp[j] + s[i]);
                if (dp[i] >= k)
                {
                    ans = min(ans, g);
                    return true;
                }
            }
        }
    return false;
}
int main()
{
    scanf("%lld%lld%lld", &n, &d, &k);
    for (ll i = 1; i <= n; i++)
        scanf("%lld%lld", x + i, s + i);
    ll left = 1, right = 10;
    bool flag = false;
    ans = INF;
    while (left <= right)
    {
        ll mid = (left + right) >> 1;
        if (maxslidingwindow(mid))
        {
            right = mid - 1;
            flag = true;
        }
        else
        {
            left = mid + 1;
        }
    }
    (flag) ? printf("%lld", ans) : printf("-1");
}