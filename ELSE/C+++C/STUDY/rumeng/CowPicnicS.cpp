// 2 4 4
// 2
// 3
// 1 2
// 1 4
// 2 3
// 3 4
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 10000001
int vis[MAX], head[MAX], nums[MAX], idx, k, n, m, cows[MAX], ans;
struct Node
{
    int to, nex;
} edge[MAX];
void dfs(int x)
{
    vis[x] = 1;
    nums[x]++;
    for (int i = head[x]; i; i = edge[i].nex)
    {
        int to = edge[i].to;
        if (!vis[to])
            dfs(to);
    }
}
void add(int u, int v)
{
    edge[++idx] = (Node){v, head[u]};
    head[u] = idx;
}
void input()
{
    cin >> k >> n >> m;
    for (int i = 1; i <= k; i++)
    {
        scanf("%d", cows + i);
    }
    for (int i = 1; i <= m; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b);
    }
}
int main()
{
    input();
    for (int i = 1; i <= k; i++)
    {
        memset(vis, 0, sizeof(vis));
        dfs(cows[i]);
    }
    for (int i = 1; i <= n; i++)
    {
        if (nums[i] == k)
            ans++;
    }
    printf("%d", ans);
}