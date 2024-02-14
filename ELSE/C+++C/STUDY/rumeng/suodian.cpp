#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 1000005
int cnt, suo[MAX], val[MAX], suo_sum[MAX];
int dfn[MAX], low[MAX], tim, vis[MAX];
int idx, head[MAX];
int n, m;
struct Node
{
    int from, to, nex;
} edge[MAX];
void add(int u, int v)
{
    edge[++idx] = (Node){u, v, head[u]};
    head[u] = idx;
}
stack<int> S;
void tarjan(int now)
{
    dfn[now] = low[now] = ++tim;
    S.push(now);
    vis[now] = 1;
    for (int i = head[now]; i; i = edge[i].nex)
    {
        int to = edge[i].to;
        if (!dfn[to])
        {
            tarjan(to);
            low[now] = min(low[now], low[to]);
        }
        else if (vis[to])
            low[now] = min(low[now], low[to]);
    }
    if (dfn[now] == low[now])
    {
        int t;
        cnt++;
        while (!S.empty())
        {
            t = S.top();
            S.pop();
            vis[t] = 0;
            suo[t] = cnt;
            suo_sum[cnt] += val[t];
            if (t == now)
                break;
        }
    }
}
void input()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        scanf("%d", val + i);
    for (int i = 1; i <= m; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b);
    }
}
int new_head[MAX], new_idx;
struct NodeNode
{
    int from, to, nex;
} new_edge[MAX];
int dutt[MAX];
void rebuild()
{
    for (int i = 1; i <= m; i++)
    {
        int x = suo[edge[i].from], y = suo[edge[i].to];
        if (x != y)
        {
            new_edge[++new_idx] = (NodeNode){x, y, new_head[x]};
            new_head[x] = new_idx;
            dutt[y]++;
        }
    }
}
queue<int> q;
int anss[MAX];
int tupo()
{
    for (int i = 1; i <= cnt; i++)
        if (!dutt[i])
        {
            anss[i] = suo_sum[i];
            q.push(i);
        }
    while (!q.empty())
    {
        int now = q.front();
        q.pop();
        for (int i = new_head[now]; i; i = new_edge[i].nex)
        {
            int to = new_edge[i].to;
            anss[to] = max(anss[to], anss[now] + suo_sum[to]);
            dutt[to]--;
            if (!dutt[to])
                q.push(to);
        }
    }
    int ans = 0;
    for (int i = 1; i <= cnt; i++)
        ans = max(ans, anss[i]);
    return ans;
}
int main()
{
    input();
    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            tarjan(i);
    rebuild();
    cout << tupo();
}