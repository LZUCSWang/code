#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 10000000

int ans, low[MAX], dfn[MAX], tim;
bool vis[MAX];
int head[MAX], idx;
struct Node
{
    int to, nex;
} edge[MAX];
void add(int u, int v)
{
    edge[++idx] = Node{v, head[u]};
    head[u] = idx;
}
stack<int> s;
void tarjan(int now)
{
    dfn[now] = low[now] = ++tim;
    vis[now] = true;
    s.push(now);
    for (int i = head[now]; i; i = edge[i].nex)
    {
        int to = edge[i].to;
        if (!dfn[to])
        {
            tarjan(to);
            low[now] = min(low[now], low[to]);
        }
        else if (vis[to])
            low[now] = min(low[now], dfn[to]);
    }
    if (dfn[now] == low[now])
    {
        if (now != s.top())
        {
            ans++;
            while (now != s.top())
                vis[s.top()] = false, s.pop();
        }
        vis[s.top()] = false;
        s.pop();
    }
}
int n, m;
void input()
{
    cin >> n >> m;
    for (int i = 1, a, b; i <= m; i++)
    {
        scanf("%d%d", &a, &b);
        add(a, b);
    }
}
int main()
{
    input();
    for (int i = 1; i <= n; i++)
    {
        if (!dfn[i])
            tarjan(i);
    }
    printf("%d", ans);
}