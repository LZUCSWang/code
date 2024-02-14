#include <bits/stdc++.h>
using namespace std;
#define MAX 10000001
long long n, m, q;
long long idx;
long long head[MAX], parent[MAX];
struct node
{
    long long to, nex, w;
} edges[MAX];
void add(long long u, long long v, long long w)
{
    edges[++idx].to = v;
    edges[idx].w = w;
    edges[idx].nex = head[u];
    head[u] = idx;
}
long long seen[MAX];
void input()
{
    cin >> n >> m >> q;
    while (m--)
    {
        long long u, v, w;
        scanf("%lld%lld%lld", &u, &v, &w);
        add(u, v, w);
        add(v, u, w);
    }
}
long long dis[MAX];
void bfs(long long s)
{
    queue<long long> q;
    q.push(s);
    while (!q.empty())
    {
        long long now_ = q.front();
        q.pop();
        if (seen[now_])
            continue;
        seen[now_] = 1;
        for (long long i = head[now_]; i; i = edges[i].nex)
        {
            dis[edges[i].to] = dis[now_] ^ edges[i].w;
            q.push(edges[i].to);
        }
    }
}
int main()
{
    input();
    bfs(1);
    while (q--)
    {
        long long a, b;
        scanf("%lld%lld", &a, &b);
        printf("%lld\n", dis[a] ^ dis[b]);
    }
}