#include <bits/stdc++.h>
using namespace std;
#define N 60
#define INF 2e9

int n, m;
bool dp[N][N][100];
int dis[N][N];
int main()
{
    cin >> n >> m;
    memset(dis, 0x3f, sizeof(dis));
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v),
            dp[u][v][0] = true,
            dis[u][v] = 1;
    for (int p = 1; p <= 65; p++)
        for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    if (dp[i][k][p - 1] && dp[k][j][p - 1])
                        dp[i][j][p] = true,
                        dis[i][j] = 1;
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
    printf("%d", dis[1][n]);
}