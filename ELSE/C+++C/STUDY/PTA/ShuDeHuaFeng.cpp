#include <bits/stdc++.h>
using namespace std;
#define MAXN 1005
int ans, N, K;
void dfs(int nowStartNum, int nowSum, int nowCnt)
{
    if (nowCnt == K)
    {
        if (nowSum == N)
        {
            ans++;
        }
        return;
    }
    for (int i = nowStartNum; i * (K - nowCnt) + nowSum <= N; i++)
    {
        dfs(i, nowSum + i, nowCnt + 1);
    }
}
int dp[MAXN][8];
int main()
{
    ios::sync_with_stdio(false);
    cin >> N >> K;
    // dfs(1, 0, 0);
    for (int i = 0; i <= N; i++)
    {
        dp[i][0] = 0;
    }
    for (int j = 0; j <= K; j++)
    {
        dp[0][j] = 0;
    }
    for (int i = 1; i <= N; i++)
    {
        dp[i][1] = 1;
    }
    for (int j = 2; j <= K; j++)
    {
        for (int i = 1; i <= N; i++)
        {
            dp[i][j] = dp[i - 1][j - 1];
            if (i >= j)
                dp[i][j] += dp[i - j][j];
        }
    }
    // for (int j = 0; j <= K; j++)
    // {
    //     for (int i = 0; i <= N; i++)
    //     {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    ans = dp[N][K];
    cout << ans;
}