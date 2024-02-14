// https://www.luogu.com.cn/problem/P1546
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 10000001
int n, k;
int parent[MAX];
int idx;
struct node
{
    int u, v, w;
} edges[MAX];
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
bool cmp(node a, node b)
{
    return a.w < b.w;
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
                edges[++idx].u = i;
                edges[idx].v = j;
                edges[idx].w = t;
            }
        }
    }

    sort(edges + 1, edges + 1 + idx, cmp);
}
void kursal()
{
    init();
    for (int i = 1; i <= idx; i++)
    {
        int fx = fa(edges[i].u), fy = fa(edges[i].v);
        if (fx != fy)
        {
            parent[fx] = fy;
            ans += edges[i].w;
            cnt++;
        }
        if (cnt == n - 1)
        {
            break;
        }
    }
    printf("%lld", ans);
}
int main()
{
    input();
    kursal();
}