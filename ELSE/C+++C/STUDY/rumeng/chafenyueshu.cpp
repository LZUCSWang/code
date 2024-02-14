#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 10000000

int head[MAX], idx;
struct Node
{
    int to, dis, nex;
} edge[MAX];
void add(int u, int v, int dis)
{
    edge[++idx] = Node{v, dis, head[u]};
    head[u] = idx;
}
queue<int> q;
int n, m;
int cnt[MAX], dis[MAX];
bool in[MAX];
bool spfa(int start)
{
    q.push(start);
    in[start] = true;
    for (int i = 1; i <= n; i++)
    {
        dis[i] = INF;
    }
    dis[start] = 0;
    cnt[start]++;
    while (!q.empty())
    {
        int now = q.front();
        q.pop();
        in[now] = false;
        for (int i = head[now]; i; i = edge[i].nex)
        {
            int to = edge[i].to;
            if (dis[to] > edge[i].dis + dis[now])
            {
                dis[to] = edge[i].dis + dis[now];
                if (!in[to])
                {
                    in[to] = true;
                    cnt[to]++;
                    if (cnt[to] == n + 1)
                    {
                        return false;
                    }
                    q.push(to);
                }
            }
        }
    }
    return true;
}
void input()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        add(0, i, 0);
    for (int i = 1, a, b, c, d; i <= m; i++)
    {
        scanf("%d", &d);
        if (d == 2)
        {
            scanf("%d%d%d", &a, &b, &c);
            add(b, a, c);
        }
        else if (d == 1)
        {
            scanf("%d%d%d", &a, &b, &c);
            add(a, b, -c);
        }
        else
        {
            scanf("%d%d", &a, &b);
            add(a, b, 0);
            add(b, a, 0);
        }
    }
}
int main()
{
    input();
    if (!spfa(0))
        printf("No");
    else
        printf("Yes");
}