#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 10100

int n, m, k;
int up[MAX], down[MAX];
int low[MAX], high[MAX];
bool flag[MAX];
void input()
{
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++)
        scanf("%d%d", up + i, down + i);
    for (int i = 1; i <= n; i++)
    {
        low[i] = 0;
        high[i] = m + 1;
    }
    for (int i = 1, p, h, l; i <= k; i++)
    {
        scanf("%d%d%d", &p, &l, &h);
        flag[p] = true;
        low[p] = l;
        high[p] = h;
    }
}   
int dp[MAX][2100];
void init()
{
    memset(dp, 0x3f3f3f, sizeof(dp));
    for (int j = 1; j <= m; j++)
        dp[0][j] = 0;
}
void solve()
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = up[i] + 1; j <= m + up[i]; j++) //上升,点一次（从左下来）或多次（原地上升）
            dp[i][j] = min(dp[i - 1][j - up[i]] + 1, dp[i][j - up[i]] + 1);
        for (int j = m + 1; j <= m + up[i]; j++) //处理上升过程的越界情况
            dp[i][m] = min(dp[i][j], dp[i][m]);
        for (int j = 1; j <= m - down[i]; j++) //下降，不点（从左上来）
            dp[i][j] = min(dp[i - 1][j + down[i]], dp[i][j]);
        for (int j = 1; j <= low[i]; j++) //处理撞墙情况
            dp[i][j] = dp[0][0];
        for (int j = high[i]; j <= m; j++)
            dp[i][j] = dp[0][0];
    }
}
void output()
{
    int ans = dp[0][0];
    for (int j = 1; j <= m; j++)
        ans = min(ans, dp[n][j]);
    if (ans < dp[0][0])
        printf("1\n%d\n", ans);
    else
    {
        int i, j;
        for (i = n, ans = 0; i; i--)
        {
            for (j = 1; j <= m; j++)
                if (dp[i][j] < dp[0][0])
                    break;
            if (j <= m)
                break;
        }
        for (int k = 1; k <= i; k++)
            if (flag[k])
                ans++;
        printf("0\n%d\n", ans);
        exit(0);
    }
}

int main()
{
    input();
    init();
    solve();
    output();
}