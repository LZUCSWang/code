#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 100000

// 6 6
// 1 2
// 1 3
// 2 6
// 2 5
// 4 5
// 3 4
// 1 5

int head[MAX], idx;
struct Node
{
    int to, nex;
} edge[MAX * 100];
void add(int u, int v)
{
    edge[++idx] = Node{v, head[u]};
    head[u] = idx;
}
int n, m, s, e;
inline void fan_build()
{
    cin >> n >> m;
    for (int i = 1, a, b; i <= m; i++)
    {
        scanf("%d%d", &a, &b);
        add(b, a);
    }
    cin >> s >> e;
}
int vis1[MAX], vis2[MAX];
queue<int> q;
inline void bfs1()
{
    q.push(e);
    while (!q.empty())
    {
        int now = q.front();
        q.pop();
        for (int i = head[now]; i; i = edge[i].nex)
        {
            int to = edge[i].to;
            if (!vis1[to])
            {
                vis1[to] = 1;
                q.push(to);
            }
        }
    }
}
inline void find_dot()
{
    memcpy(vis2, vis1, sizeof(vis2));
    for (int i = 1; i <= n; i++)
    {
        if (!vis1[i] && i != e)
            for (int j = head[i]; j; j = edge[j].nex)
            {
                int to = edge[j].to;
                if (vis2[to])
                    vis2[to] = 0;
            }
    }
}
int ans[MAX];
inline void bfs2()
{
    q.push(e);
    vis2[e] = 0;
    while (!q.empty())
    {
        int now = q.front();
        q.pop();
        for (int i = head[now]; i; i = edge[i].nex)
        {
            int to = edge[i].to;
            if (vis2[to])
            {
                ans[to] = ans[now] + 1;
                vis2[to] = 0;
                q.push(to);
            }
        }
    }
}
int main()
{
    fan_build();
    bfs1();
    find_dot();
    bfs2();
    if (ans[s] == 0)
        cout << -1;
    else
        cout << ans[s];
    return 0;
}