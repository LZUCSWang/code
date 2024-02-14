// https://www.luogu.com.cn/problem/P1833
// 6:50 7:00 3
// 2 1 0
// 3 3 1
// 4 5 4
#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 10000000
int cnt;
int sh, sm, eh, em, n;
int v[MAX], w[MAX], dp[MAX];
int T;
void input()
{
    scanf("%d:%d %d:%d %d", &sh, &sm, &eh, &em, &n);
    T = eh * 60 + em - sh * 60 - sm;
    for (int i = 1, ww, vv, tt; i <= n; i++)
    {
        scanf("%d%d%d", &ww, &vv, &tt);
        if (!tt)
        {
            tt = 999999;
        }
        for (int k = 1; k < tt; k <<= 1)
        {
            v[++cnt] = vv * k;
            w[cnt] = ww * k;
            tt -= k;
        }
        v[++cnt] = vv * tt;
        w[cnt] = ww * tt;
    }
}
int main()
{
    input();
    for (int i = 1; i <= cnt; i++)
    {
        for (int j = T; j >= w[i]; j--)
        {
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
        }
    }
    printf("%d", dp[T]);
}