#include <bits/stdc++.h>
using namespace std;
#define MAXN 1005
typedef long long ll;
int dp[MAXN];
ll n, ans = 1;
// void dfs(ll x)
// {
//     if (n == 1)
//     {
//         ans++;
//         return;
//     }
//     for (int i = x / 2; i >= 1; i--)
//     {
//         ans++;
//         dfs(i);
//     }
// }
int main()
{
    ios::sync_with_stdio(false);
    cin >> n;
    // if (n != 1)
    //     dfs(n);
    cout << ans << endl;

    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        if (i & 1)
        {
            dp[i] = dp[i - 1];
        }
        else
        {
            dp[i] = dp[i - 1] + dp[i / 2];
        }
    }
    cout << dp[n] << endl;
}