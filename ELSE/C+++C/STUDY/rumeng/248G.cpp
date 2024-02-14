#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 1000

int n;
int dp[MAX][MAX], ans;
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> dp[i][i];
    for (int step = 2; step <= n; step++)
        for (int l = 1, r = l + step - 1; r <= n; l++, r++)
            for (int k = l; k < r; k++)
                if (dp[l][k] && dp[l][k] == dp[k + 1][r])
                    dp[l][r] = max(dp[l][r], dp[l][k] + 1), ans = max(ans, dp[l][r]);
    printf("%d", ans);
}