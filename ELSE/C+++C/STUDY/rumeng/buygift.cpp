#include <bits/stdc++.h>
#define N 100001
using namespace std;
long long n, a, x, y, l, sum, ans;
long long parent[N];
struct Edge
{
    long long u, v, w;
} edge[N * 10];
bool operator<(Edge a, Edge b)
{
    return a.w < b.w;
}
long long idx;
long long find(long long x)
{
    return parent[x] == x ? parent[x] : parent[x] = find(parent[x]);
}
void builds(long long u, long long v, long long w)
{
    edge[idx].u = u;
    edge[idx].v = v;
    edge[idx++].w = w;
}
int main()
{
    scanf("%lld%lld", &a, &n);
    for (long long i = 1; i <= n; i++)
        parent[i] = i;
    for (long long i = 1; i <= n; i++)
    {
        builds(0, i, a);
        for (long long j = 1; j <= n; j++)
        {
            long long x;
            scanf("%d", &x);
            if (i < j && x)
            {
                builds(i, j, x);
            }
        }
    }
    sort(edge, edge + idx);
    for (long long i = 0; i <= idx - 1; i++)
    {
        long long fx = find(edge[i].u), fy = find(edge[i].v);
        if (fx != fy)
        {
            parent[fx] = fy;
            sum++;
            ans += edge[i].w;
        }
        if (sum == n)
        {
            printf("%lld", ans);
            return 0;
        }
    }
    // puts("No Answer");
    printf("%lld", ans);
    return 0;
}