// https://www.luogu.com.cn/problem/P1807
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 10000001
// 2 1
// 1 2 1
ll idx, head[MAX], dutt[MAX], n, m;
queue<ll> q;
ll dis[MAX];
struct Node
{
    ll to, w, nex;
} edge[MAX];
void add(ll u, ll v, ll w)
{
    edge[++idx] = (Node){v, w, head[u]};
    head[u] = idx;
}
void bfs()
{
    memset(dis, -0x7f, sizeof(dis));
    for (ll i = 1; i <= n; i++)
    {
        if (!dutt[i])
            q.push(i);
        if (i == 1)
            dis[i] = 0;
        else
            dis[i] = -MAX;
    }
    while (!q.empty())
    {
        ll t = q.front();
        q.pop();
        for (ll i = head[t]; i; i = edge[i].nex)
        {
            ll v = edge[i].to;
            dutt[v]--;
            dis[v] = max(dis[v], dis[t] + edge[i].w);
            if (dutt[v] == 0)
                q.push(v);
        }
    }
    if (dis[n] < 0)
        printf("-1");
    else
        printf("%lld", dis[n]);
}
void input()
{
    cin >> n >> m;
    for (ll i = 1; i <= m; i++)
    {
        ll a, b, c;
        scanf("%lld%lld%lld", &a, &b, &c);
        dutt[b]++;
        add(a, b, c);
    }
}
int main()
{
    input();
    bfs();
}