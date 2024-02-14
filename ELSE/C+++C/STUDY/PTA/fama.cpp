#include <bits/stdc++.h>
using namespace std;
#define MAXN 10000
int w[MAXN];
int n;
int Max = 0;
int dp[MAXN][MAXN];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", w + i);
        Max += w[i];
    }
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= Max; j++)
        {
            dp[i][j] = dp[i - 1][j] + dp[i - 1][j + w[i]] + dp[i - 1][abs(j - w[i])];
        }
    }
    int ans = 0;
    for (int i = 1; i <= Max; i++)
    {
        if (dp[n][i])
        {
            // printf("%d ", i);
            ans++;
        }
    }
    printf("%d", ans);
}