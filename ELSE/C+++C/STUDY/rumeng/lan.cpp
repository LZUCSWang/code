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
    cin >> n >> k;
    while (k--)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        if (c == 0)
            continue;
        edges[++idx].u = a;
        edges[idx].v = b;
        edges[idx].w = c;
        sum += c;
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
    printf("%lld", sum - ans);
}
int main()
{
    input();
    kursal();
}