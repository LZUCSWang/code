// https://www.luogu.com.cn/problem/P1525
#include <bits/stdc++.h>
using namespace std;
#define MAX 10000001
int n, m, parent[MAX], flag[MAX];
struct Node
{
    int x, y, w;
} edge[MAX];
int fa(int x)
{
    return x == parent[x] ? x : parent[x] = fa(parent[x]);
}
void work()
{
    for (int i = 1; i <= m + 1; i++)
    {
        int x = edge[i].x, y = edge[i].y, fx = fa(x), fy = fa(y);
        if (fx == fy)
        {
            printf("%d", edge[i].w);
            exit(0);
        }
        if (flag[x] == 0)
            flag[x] = y;
        else
            parent[fa(flag[x])] = fy;
        if (flag[y] == 0)
            flag[y] = x;
        else
            parent[fa(flag[y])] = fx;
    }
}
bool cmp(Node a, Node b)
{
    return a.w > b.w;
}
void init()
{
    for (int i = 1; i <= n; i++)
        parent[i] = i;
}
void input()
{
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        edge[i] = (Node){a, b, c};
    }
    sort(edge + 1, edge + 1 + m, cmp);
}
int main()
{
    input();
    init();
    work();
}