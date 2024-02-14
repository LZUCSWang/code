#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 1000000
// https://www.luogu.com.cn/problem/P1776
int n, W;
int cnt;
int v[MAX], w[MAX], dp[MAX];
int main()
{
    scanf("%d%d", &n, &W);
    for (int i = 1, vv, ww, ss; i <= n; i++)
    {
        scanf("%d%d%d", &vv, &ww, &ss);
        for (int k = 1; k < ss; k <<= 1)
        {
            v[++cnt] = vv * k;
            w[cnt] = ww * k;
            ss -= k;
        }
        v[++cnt] = vv * ss;
        w[cnt] = ww * ss;
    }
    for (int i = 1; i <= cnt; i++)
        for (int j = W; j >= w[i]; j--)
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
    printf("%d", dp[W]);
}