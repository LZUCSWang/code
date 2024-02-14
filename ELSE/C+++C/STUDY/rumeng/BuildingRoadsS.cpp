#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 40500001
#define M 1001
// 4 1
// 1 1
// 3 1
// 2 3
// 4 3
// 1 4
ll parent[M];
ll n, m;
ll idx, cnt;
double ans;
struct node
{
    ll x, y;
} point[MAX];
struct Node
{
    ll u, v, w;
} edge[MAX];
bool cmp(Node a, Node b)
{
    return a.w < b.w;
}
void init()
{
    for (ll i = 1; i <= n; i++)
    {
        parent[i] = i;
    }
}
int flag[M][M];
ll fa(ll x)
{
    return (x == parent[x]) ? x : parent[x] = fa(parent[x]);
}
void input()
{
    cin >> n >> m;
    for (ll i = 1; i <= n; i++)
    {
        scanf("%lld%lld", &point[i].x, &point[i].y);
    }
    init();
    for (ll i = 1; i <= m; i++)
    {
        ll a, b;
        scanf("%lld%lld", &a, &b);
        a = fa(a), b = fa(b);
        if (a != b)
        {
            parent[a] = b;
            cnt++;
        }
        flag[a][b] = flag[b][a] = 1;
    }
    for (ll i = 1; i <= n; i++)
    {
        for (ll j = 1 + i; j <= n; j++)
        {
            if (flag[i][j] == 1)
                continue;
            edge[++idx] = (Node){i, j, (ll)(1ll * (point[i].x - point[j].x) * (point[i].x - point[j].x) + 1ll * (point[i].y - point[j].y) * (point[i].y - point[j].y))};
        }
    }
    sort(edge + 1, edge + 1 + idx, cmp);
}
void kur()
{
    for (ll i = 1; i <= idx; i++)
    {
        ll fx = fa(edge[i].u), fy = fa(edge[i].v);
        if (fx != fy)
        {
            parent[fx] = fy;
            ans += pow(edge[i].w, 0.5);
            cnt++;
        }
        if (cnt == n - 1)
        {
            printf("%.2lf", ans);
            exit(0);
        }
    }
    printf("%.2lf",ans);
}
int main()
{
    input();
    kur();
}