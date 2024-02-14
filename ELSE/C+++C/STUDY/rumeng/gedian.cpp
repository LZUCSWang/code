#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 10000001
int tim, dfn[MAX], low[MAX];
int idx, head[MAX];
struct Node
{
    int to, nex;
} edge[MAX];

void add(int u, int v)
{
    edge[++idx] = (Node){v, head[u]};
    head[u] = idx;
}
int gen, flag[MAX];
void tarjan(int now)
{
    int cnt = 0;
    dfn[now] = low[now] = ++tim;
    for (int i = head[now]; i; i = edge[i].nex)
    {
        int to = edge[i].to;
        if (!dfn[to])
        {
            tarjan(to);
            low[now] = min(low[now], low[to]);
            if (low[to] >= dfn[now] && now != gen)
                flag[now] = 1;
            if (now == gen)
                cnt++;
        }
        low[now] = min(low[now], dfn[to]);
    }
    if (cnt >= 2 && now == gen)
        flag[now] = 1;
}
int n, m;
void input()
{
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b), add(b, a);
    }
}
int main()
{
    input();
    for (int i = 1; i <= n; i++)
    {
        if (!dfn[i])
        {
            gen = i;
            tarjan(i);
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
        if (flag[i])
            ans++;
    printf("%d\n", ans);
    for (int i = 1; i <= n; i++)
        if (flag[i])
            printf("%d ", i);
}