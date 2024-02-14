#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 1000001
ll parent[MAX];
ll fa(ll x)
{
    return (x == parent[x]) ? x : parent[x] = fa(parent[x]);
}
struct node
{
    ll u, v, t;
} edges[MAX];
ll n, m;
bool cmp(node a, node b)
{
    return a.t < b.t;
}
void input()
{
    cin >> n >> m;
    for (ll i = 1; i <= m; i++)
    {
        scanf("%lld%lld%lld", &edges[i].u, &edges[i].v, &edges[i].t);
    }
    sort(edges + 1, edges + 1 + m, cmp);
}
ll cnt;
void init()
{
    for (ll i = 1; i <= n; i++)
    {
        parent[i] = i;
    }
}
void work()
{
    init();
    for (ll i = 1; i <= m; i++)
    {
        ll fx = fa(edges[i].u), fy = fa(edges[i].v);
        if (fx != fy)
        {
            cnt++;
            if (cnt == n - 1)
            {
                printf("%lld", edges[i].t);
                exit(0);
            }
            parent[fx] = fy;
        }
    }
    printf("-1");
}
int main()
{
    input();
    work();
}