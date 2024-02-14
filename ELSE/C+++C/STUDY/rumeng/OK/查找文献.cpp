// https://www.luogu.com.cn/problem/P5318
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 10000001
int head[MAX], idx, n, m, vis[MAX], sortt[MAX];
struct Node
{
    int to, nex;
} edge[MAX];
void add(int u, int v)
{
    edge[++idx] = (Node){v, head[u]};
    head[u] = idx;
}
void dfs(int s)
{
    priority_queue<int, vector<int>, greater<int>> q;
    printf("%d ", s);
    vis[s] = 1;
    for (int i = head[s]; i; i = edge[i].nex)
    {
        int to = edge[i].to;
        if (!vis[to])
            q.push(to);
    }
    while (!q.empty())
    {
        int to = q.top();
        q.pop();
        if (!vis[to])
            dfs(to);
    }
}
void bfs(int s)
{
    queue<int> q;
    q.push(s);
    printf("%d ", s);
    vis[s] = 1;
    while (!q.empty())
    {
        int from = q.front();
        q.pop();
        int k = 0;
        for (int i = head[from]; i; i = edge[i].nex)
        {
            int to = edge[i].to;
            if (!vis[to])
            {
                vis[to] = 1;
                sortt[++k] = to;
            }
        }
        sort(sortt + 1, sortt + k + 1);
        for (int i = 1; i <= k; i++)
        {
            printf("%d ", sortt[i]);
            q.push(sortt[i]);
        }
    }
}
void input()
{
    cin >> n >> m;
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
    dfs(1);
    printf("\n");
    memset(vis, 0, sizeof(vis));
    bfs(1);
    // bfs(1);
}