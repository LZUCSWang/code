#include <bits/stdc++.h>
using namespace std;

int dp[105][105];
int n, m;
int ans;
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            int t;
            scanf("%d", &t);
            if (t == 1)
                dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1])) + 1;
            ans = max(dp[i][j], ans);
        }
    }
    printf("%d", ans);
}
