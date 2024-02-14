// https://www.luogu.com.cn/problem/P3958
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 1005
ll x[MAX], y[MAX], z[MAX], vis[MAX];
int n, r, h, t;
queue<int> q;
double dis(int a, int b)
{
    return sqrt((x[a] - x[b]) * (x[a] - x[b]) + (y[a] - y[b]) * (y[a] - y[b]) + (z[a] - z[b]) * (z[a] - z[b]));
}
void init()
{
    memset(vis, 0, sizeof(vis));
    memset(x, 0, sizeof(x));
    memset(y, 0, sizeof(y));
    memset(z, 0, sizeof(z));
    while (!q.empty())
        q.pop();
}
void bfs()
{
    while (!q.empty())
    {
        int from = q.front();
        q.pop();
        for (int i = 1; i <= n; i++)
        {
            if (vis[i])
                continue;
            if (dis(from, i) <= (double)(2 * r))
            {
                vis[i] = 1;
                q.push(i);
                if (z[i] + r >= h)
                {
                    printf("Yes\n");
                    return;
                }
            }
        }
    }
    printf("No\n");
    return;
}
void input()
{
    init();
    cin >> n >> h >> r;
    bool flag = false;
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld%lld%lld", x + i, y + i, z + i);
        if (!flag && abs(z[i]) <= r)
        {
            if (z[i] + r >= h)
            {
                flag = true;
            }
            q.push(i);
            vis[i] = 1;
        }
    }
    if (flag)
    {
        printf("Yes\n");
        return;
    }
    bfs();
}
int main()
{
    cin >> t;
    while (t--)
    {
        input();
    }
}