#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 10000

int n, k;
int dp[MAX][MAX], ans[MAX][MAX];
void cal()
{
    dp[0][0] = 1;
    dp[1][0] = dp[1][1] = 1;
    for (int i = 2; i <= 2000; i++)
    {
        dp[i][0] = 1;
        for (int j = 1; j <= i; j++)
        {
            dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j]) % k;
            ans[i][j] = ans[i - 1][j] + ans[i][j - 1] - ans[i - 1][j - 1];
            if (!dp[i][j])
                ans[i][j]++;
        }
        ans[i][i + 1] = ans[i][i];
    }
}
int m, t;
int main()
{
    cin >> t >> k;
    cal();
    while (t--)
    {
        scanf("%d%d", &n, &m);
        m = min(m, n);
        printf("%d\n", ans[n][m]);
    }
}