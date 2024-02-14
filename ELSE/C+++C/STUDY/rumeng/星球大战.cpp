#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 400005
int n, m, k, broken[MAX], isbroken[MAX];
// https://www.luogu.com.cn/problem/P1197
// 8 13
// 0 1
// 1 6
// 6 5
// 5 0
// 0 6
// 1 2
// 2 3
// 3 4
// 4 5
// 7 1
// 7 2
// 7 6
// 3 6
// 5
// 1
// 6
// 3
// 5
// 7
int parent[MAX], idx, head[MAX], total, ans[MAX];
struct Node
{
    int fro, to, nex;
} edge[MAX];
void add(int u, int v)
{
    edge[++idx] = (Node){u, v, head[u]};
    head[u] = idx;
}
void input()
{
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b);
        add(b, a);
    }
    cin >> k;
    for (int i = 1; i <= k; i++)
    {
        int a;
        scanf("%d", broken + i);
        isbroken[broken[i]] = 1;
    }
}
void init()
{
    for (int i = 0; i < n; i++)
        parent[i] = i;
}
int fa(int x)
{
    return (x == parent[x]) ? x : parent[x] = fa(parent[x]);
}
void repair()
{
    for (int i = k; i; i--)
    {
        total++;
        int now = broken[i];
        isbroken[now] = 0;
        for (int j = head[now]; j; j = edge[j].nex)
        {
            int to = edge[j].to;
            if (!isbroken[to])
            {
                int fx = fa(now), fy = fa(to);
                if (fx != fy)
                {
                    parent[fx] = fy;
                    total--;
                }
            }
        }
        ans[i] = total;
    }
}
void rest()
{
    total = n - k;
    init();
    for (int i = 1; i <= 2 * m; i++)
    {
        int u = edge[i].fro, v = edge[i].to;
        if (!isbroken[u] && !isbroken[v])
        {
            int fu = fa(u), fv = fa(v);
            if (fu != fv)
            {
                parent[fu] = fv;
                total--;
            }
        }
    }
    ans[k + 1] = total;
}
int main()
{
    input();
    init();
    rest();
    repair();
    for (int i = 1; i <= k + 1; i++)
        printf("%d\n", ans[i]);
}