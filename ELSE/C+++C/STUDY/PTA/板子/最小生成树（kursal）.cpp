#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 10000001
int n, k, parent[MAX], idx;
struct node
{
    int u, v, w;
} edge[MAX];
void init()
{
    for (int i = 1; i <= n; i++)
    {
        parent[i] = i;
    }
}

int fa(int x)
{
    return x == parent[x] ? x : parent[x] = fa(parent[x]);
}

ll cnt, ans, sum;
void input()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            int t;
            scanf("%d", &t);
            if (j > i && t)
            {
                edge[++idx].u = i;
                edge[idx].v = j;
                edge[idx].w = t;
            }
        }
    }
    sort(edge + 1, edge + 1 + idx, [](node a, node b)
         { return a.w < b.w; });
}

void kursal()
{
    init();
    for (int i = 1; i <= idx; i++)
    {
        int fx = fa(edge[i].u), fy = fa(edge[i].v);
        if (fx != fy)
        {
            parent[fx] = fy;
            ans += edge[i].w;
            cnt++;
        }
        if (n - 1 == cnt)
            break;
    }
    printf("%lld", ans);
}
int main()
{
    input();
    kursal();
}