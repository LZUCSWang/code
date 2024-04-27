#include <bits/stdc++.h>
using namespace std;
#define MAX 1000001
struct node
{
    int a, b, d;
} edges[MAX];
bool cmp(node a, node b)
{
    return a.d < b.d;
}
int parent[MAX];
int find(int x)
{
    int r = x;
    int i = x, j;
    while (parent[r] != r)
        r = parent[r];
    while (i != r)
    {
        j = parent[i];
        parent[i] = r;
        i = j;
    }
    return r;
}
int main()
{
    int n, m;
    cin >> n >> m;
    int a, b, d;
    int ans = 0;
    for (int i = 0; i < m; i++)
        scanf("%d %d %d", &edges[i].a, &edges[i].b, &edges[i].d);
    for (int i = 1; i <= n; i++)
        parent[i] = i;
    sort(edges, edges + m, cmp);
    int cnt = 0;
    for (int i = 0; i < m; i++)
    {
        int fa = find(edges[i].a), fb = find(edges[i].b);
        if (fa != fb)
        {
            parent[fa] = fb;
            ans += edges[i].d;
            cnt++;
        }
        if (cnt == n - 1)
            break;
    }
    cout << ans;
}