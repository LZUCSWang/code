// 4 3
// 1 2 4
// 2 3 3
// 3 1 1
// 3
// 1 3
// 1 4
// 1 3
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define NMAX 10005
#define EMAX 100005
#define INF 1e9
int n, m, q;
bool vis[NMAX];
struct Node1
{
    int u, v, w;
} edge_k[EMAX];
int head[NMAX], idx;
struct Node2
{
    int to, w, nex;
} edge_[EMAX];
void add(int u, int v, int w)
{
    edge_[++idx] = (Node2){v, w, head[u]};
    head[u] = idx;
}
bool cmp(Node1 a, Node1 b)
{
    return a.w > b.w;
}
void input()
{
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d %d %d", &edge_k[i].u, &edge_k[i].v, &edge_k[i].w);
    }
    cin >> q;
    sort(edge_k + 1, edge_k + 1 + m, cmp);
}
int parent[NMAX];
void init()
{
    for (int i = 1; i <= n; i++)
        parent[i] = i;
}
int fa(int x)
{
    return (x == parent[x]) ? x : parent[x] = fa(parent[x]);
}
void kur()
{
    init();
    for (int i = 1; i <= m; i++)
    {
        int fx = fa(edge_k[i].u), fy = fa(edge_k[i].v);
        if (fx != fy)
        {
            parent[fx] = fy;
            add(edge_k[i].u, edge_k[i].v, edge_k[i].w);
            add(edge_k[i].v, edge_k[i].u, edge_k[i].w);
        }
    }
}
int f[NMAX][21], w[NMAX][21], deep[NMAX];
void dfs(int now)
{
    vis[now] = true;
    for (int i = head[now]; i; i = edge_[i].nex)
    {
        int to = edge_[i].to;
        if (!vis[to])
        {
            f[to][0] = now;
            w[to][0] = edge_[i].w;
            deep[to] = deep[now] + 1;
            vis[to] = true;
            dfs(to);
        }
    }
}

int lca(int x, int y)
{
    if (fa(x) != fa(y))
        return -1;
    if (deep[x] > deep[y])
    {
        swap(x, y);
    }
    int ans = INF;
    for (int i = 20; i >= 0; i--)
    {
        if (deep[f[y][i]] >= deep[x])
        {
            ans = min(ans, w[y][i]);
            y = f[y][i];
        }
    }
    if (x == y)
    {
        return ans;
    }
    for (int i = 20; i >= 0; i--)
    {
        if (f[x][i] != f[y][i])
        {
            ans = min(ans, min(w[x][i], w[y][i]));
            x = f[x][i], y = f[y][i];
        }
    }
    return min(ans, min(w[x][0], w[y][0]));
}
int main()
{
    input();
    kur();
    for (int i = 1; i <= n; i++)
    {
        if (!vis[i])
        {
            deep[i] = 1;
            dfs(i);
            f[i][0] = i;
            w[i][0] = INF;
        }
    }
    for (int i = 1; i <= 20; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            f[j][i] = f[f[j][i - 1]][i - 1];
            w[j][i] = min(w[j][i - 1], w[f[j][i - 1]][i - 1]);
        }
    }
    for (int i = 1; i <= q; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        printf("%d\n", lca(a, b));
    }
}