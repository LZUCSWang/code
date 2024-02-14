// https://www.luogu.com.cn/problem/P2910
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 10000001
int n, m, ways[MAX], f[105][105];
void input()
{
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d", ways + i);
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            scanf("%d", &f[i][j]);
        }
    }
}
void floyd()
{
    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (f[i][j] > f[i][k] + f[k][j])
                {
                    f[i][j] = f[i][k] + f[k][j];
                }
            }
        }
    }
}
ll ans;
int main()
{
    input();
    floyd();
    for (int i = 1; i <= m - 1; i++)
    {
        ans += f[ways[i]][ways[i + 1]];
    }
    printf("%lld", ans);
}