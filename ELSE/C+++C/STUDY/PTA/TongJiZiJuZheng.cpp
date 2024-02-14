#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll dp[1005][1005];
ll N, M, K;
int main()
{
    ios::sync_with_stdio(false);
    cin >> N >> M >> K;
    for (ll i = 1; i <= N; i++)
    {
        for (ll j = 1; j <= M; j++)
        {
            cin >> dp[i][j];
            dp[i][j] += dp[i - 1][j];
        }
    }
    // cout << endl;
    // for (ll i = 1; i <= N; i++)
    // {
    //     for (ll j = 1; j <= M; j++)
    //     {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    ll ans = 0;
    for (ll up = 1; up <= N; up++)
    {
        for (ll low = up; low <= N; low++)
        {
            ll sum = 0;
            ll r = 0, l = 1;
            for (r = 1; r <= M; r++)
            {
                sum += dp[low][r] - dp[up - 1][r];
                while (sum > K)
                {
                    sum -= dp[low][l] - dp[up - 1][l];
                    l++;
                }
                ans += r - l + 1;
            }
        }
    }
    cout << ans << endl;
}