#include <bits/stdc++.h>
using namespace std;
#define MAX 55
int dp[MAX][MAX][MAX][MAX];
int datas[MAX][MAX];
int n, m;
// https://www.luogu.com.cn/problem/P1006
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &datas[i][j]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            for (int p = i + 1; p <= n; p++)
                for (int q = 1; q <= j - 1; q++)
                    dp[i][j][p][q] = max(dp[i - 1][j][p - 1][q], max(dp[i - 1][j][p][q - 1], max(dp[i][j - 1][p - 1][q], dp[i][j - 1][p][q - 1]))) + datas[i][j] + datas[p][q];
    printf("%d", dp[n - 1][m][n][m - 1]);
}