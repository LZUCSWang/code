#include <bits/stdc++.h>
#define N 1005
using namespace std;
int n, m, k, x, y, l, sum, ans;
int parent[N];
struct Edge
{
    int u, v, w;
} edge[N * 10];
bool operator<(Edge a, Edge b)
{
    return a.w < b.w;
}
int find(int x)
{
    return parent[x] == x ? parent[x] : parent[x] = find(parent[x]);
}
int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++)
        parent[i] = i;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &edge[i].u, &edge[i].v, &edge[i].w);
    }
    sort(edge + 1, edge + m + 1);
    for (int i = 1; i <= m; i++)
    {
        int fx = find(edge[i].u), fy = find(edge[i].v);
        if (fx != fy)
        {
            parent[fx] = fy;
            sum++;
            ans += edge[i].w;
        }
        if (sum == n - k)
        {
            printf("%d", ans);
            return 0;
        }
    }
    puts("No Answer");
    return 0;
}