#include <bits/stdc++.h>
using namespace std;
#define MAX 1000001
long long idx;
long long head[MAX];
long long depth[MAX];
long long fa[MAX][21];
long long n, m, s;
long long lg[MAX];
struct node
{
    long long to, nex;
} edges[MAX];
void add(long long u, long long v)
{
    edges[++idx].to = v;
    edges[idx].nex = head[u];
    head[u] = idx;
}

void input()
{
    cin >> n >> m >> s;

    for (long long i = 0; i < n - 1; i++)
    {
        long long a, b;
        scanf("%lld%lld", &a, &b);
        add(a, b);
        add(b, a);
    }
}
void dfs(long long now, long long faer)
{
    fa[now][0] = faer;
    depth[now] = depth[faer] + 1;
    for (long long i = 1; i <= log2(depth[now]); i++)
    {
        fa[now][i] = fa[fa[now][i - 1]][i - 1];
    }
    for (long long i = head[now]; i; i = edges[i].nex)
    {
        if (edges[i].to != faer)
        {
            dfs(edges[i].to, now);
        }
    }
}

long long LCA(long long a, long long b)
{
    if (depth[a] < depth[b])
    {
        swap(a, b);
    }
    while (depth[a] > depth[b])
    {
        a = fa[a][lg[depth[a] - depth[b]] - 1];
    }
    if (a == b)
    {
        return a;
    }
    for (long long i = lg[depth[a]] - 1; i >= 0; i--)
    {
        if (fa[a][i] != fa[b][i])
        {
            a = fa[a][i];
            b = fa[b][i];
        }
    }
    return fa[a][0];
}
void init_log2()
{
    for (long long i = 1; i <= n; ++i)
        lg[i] = lg[i - 1] + (1 << lg[i - 1] == i);
}
void main_work()
{
    for (long long i = 0; i < m; i++)
    {
        long long a, b;
        scanf("%lld%lld", &a, &b);
        printf("%lld\n", LCA(a, b));
    }
}
void print_log2()
{
    for (long long i = 0; i <= n; i++)
    {
        printf("%lld ", lg[i]);
    }
}
int main()
{
    input();
    init_log2();
    // print_log2();
    dfs(s, 0);
    main_work();
}