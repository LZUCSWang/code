#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 10000000

int len, S, T, M, a[105], b[105], dp[MAX];
bool flag[MAX];
int main()
{
    cin >> len;
    cin >> S >> T >> M;
    for (int i = 1; i <= M; i++)
        scanf("%d", a + i);
    sort(a + 1, a + M + 1);
    if (S == T)
    {
        int ans = 0;
        for (int i = 1; i <= M; i++)
            if (a[i] % S==0)
                ans++;
        printf("%d\n", ans);
        return 0;
    }
    for (int i = 1; i <= M; i++)
    {
        if (a[i] - a[i - 1] > 1000)
            b[i] = b[i - 1] + 1000;
        else
            b[i] = a[i] - a[i - 1] + b[i - 1];
        flag[b[i]] = true;
    }
    len = b[M];
    for (int i = 1; i <= len + T - 1; i++)
    {
        dp[i] = INF;
        for (int j = S; j <= T && j <= i; j++)
            dp[i] = min(dp[i], dp[i - j]);
        if (flag[i])
            dp[i]++;
    }
    int ans = INF;
    for (int i = len; i <= len + T - 1; i++)
        ans = min(ans, dp[i]);
    printf("%d\n", ans);
}