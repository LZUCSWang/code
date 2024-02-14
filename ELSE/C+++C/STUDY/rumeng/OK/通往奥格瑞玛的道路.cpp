// https://www.luogu.com.cn/problem/P1462
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define N 10005
#define M 50005
#define INF 2e9
int n, m, b, f[N];
int idx, head[N];
struct Node
{
    int to, w, nex;
} edge[M * 100];
void add(int u, int v, int w)
{
    edge[++idx] = (Node){v, w, head[u]};
    head[u] = idx;
}
void input()
{
    cin >> n >> m >> b;
    for (int i = 1; i <= n; i++)
        scanf("%d", f + i);
    for (int i = 1; i <= m; i++)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c);
        add(b, a, c);
    }
}
ll dis[N];
bool vis[N];
struct NODE
{
    int to;
    ll dis;
    bool operator<(NODE p) const
    {
        return dis > p.dis;
    }
};

bool diji(int x)
{
    priority_queue<NODE> q;
    if (x < f[1])
        return false;
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= n; i++)
        dis[i] = INF;
    dis[1] = 0;
    q.push((NODE){1, 0});
    while (!q.empty())
    {
        NODE now = q.top();
        q.pop();
        int from = now.to;
        if (vis[from])
            continue;
        vis[from] = true;
        for (int i = head[from]; i; i = edge[i].nex)
        {
            int to = edge[i].to;
            if (f[to] <= x && !vis[to] && dis[to] > now.dis + edge[i].w)
            {
                dis[to] = now.dis + edge[i].w;
                q.push((NODE){to, dis[to]});
            }
        }
    }
    if (dis[n] <= b)
        return true;
    return false;
}
int main()
{
    input();
    if (!diji(INF))
    {
        printf("AFK\n");
        return 0;
    }
    int left = 0, right = INF;
    while (left <= right)
    {
        int mid = (left + right) >> 1;
        if (diji(mid))
            right = mid - 1;
        else
            left = mid + 1;
    }
    printf("%d\n", left);
    return 0;
}