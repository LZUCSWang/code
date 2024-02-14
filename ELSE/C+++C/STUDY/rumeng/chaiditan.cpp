#include <bits/stdc++.h>
using namespace std;
#define MAX 10000001
struct node
{
    long long u, v, w;
} edges[MAX];
bool cmp(node a, node b)
{
    return a.w > b.w;
}
long long n, m, k;
void input()
{
    cin >> n >> m >> k;
    for (long long i = 0; i < m; i++)
    {
        long long a, b, c;
        scanf("%lld%lld%lld", &a, &b, &c);
        edges[i].u = a, edges[i].v = b, edges[i].w = c;
    }
    sort(edges, edges + m, cmp);
}
long long parent[MAX];
void init()
{
    for (long long i = 1; i <= n; i++)
    {
        parent[i] = i;
    }
}
long long fa(long long x)
{
    return (x == parent[x]) ? x : parent[x] = fa(parent[x]);
}
long long ans, cnt;
void main_work()
{
    input();
    init();
    for (long long i = 0; i < m; i++)
    {
        long long fx = fa(edges[i].u), fy = fa(edges[i].v);
        if (fx != fy)
        {
            ans += edges[i].w;
            cnt++;
            parent[fx] = fy;
        }
        if (cnt == k)
        {
            printf("%lld", ans);
            exit(0);
        }
    }
}
int main()
{
    main_work();
}