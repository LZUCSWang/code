#include <bits/stdc++.h>
using namespace std;
#define MAX 100000000
int n, m, k;
struct node
{
    int a, b, c;

} edges[MAX];
bool cmp(node x, node y)
{
    return x.c < y.c;
}
int parent[MAX];
int find(int x)
{
    return (x == parent[x]) ? x : parent[x] = find(parent[x]);
}
void init()
{
    for (int i = 1; i <= n; i++)
    {
        parent[i] = i;
    }
}
void input()
{
    cin >> n >> m >> k;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &edges[i].a, &edges[i].b, &edges[i].c);
    }
    sort(edges + 1, edges + 1 + m, cmp);
}
int cnt, ans;
void kual()
{
    init();
    for (int i = 1; i <= m; i++)
    {
        int fa = find(edges[i].a), fb = find(edges[i].b);
        if (fa != fb)
        {
            parent[fa] == fb;
            ans += edges[i].c;
            cnt++;
        }
        if (cnt == n - k)
        {
            printf("%d", ans);
            return;
            // break;
        }
    }
    printf("No Answer");
}
int main()
{
    input();
    kual();
}