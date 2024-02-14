// 4 2
// 0 0
// 0 1
// 1 1
// 1 0
// https://www.luogu.com.cn/problem/P4047
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 1005
int n, k;
struct poi
{
    int x, y;
} point[MAX];
struct Node
{
    int u, v;
    double w;
} edge[MAX * 1000];
int idx;
double dis(int i, int j)
{
    return sqrt(pow(point[i].x - point[j].x, 2) + pow(point[i].y - point[j].y, 2));
}
void input()
{
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &point[i].x, &point[i].y);
}
bool cmp(Node a, Node b)
{
    return a.w < b.w;
}
void build()
{
    for (int i = 1; i < n; i++)
        for (int j = i + 1; j <= n; j++)
            edge[++idx] = (Node){i, j, dis(i, j)};
    sort(edge + 1, edge + 1 + idx, cmp);
}
int parent[MAX];
int fa(int x)
{
    return (x == parent[x]) ? x : parent[x] = fa(parent[x]);
}
bool flag;
int cnt;
void kurs()
{
    for (int i = 1; i <= n; i++)
        parent[i] = i;
    for (int i = 1; i <= idx; i++)
    {
        if (cnt == n - k)
            flag = true;
        int fx = fa(edge[i].u), fy = fa(edge[i].v);
        if (fx != fy)
        {
            if (flag)
            {
                printf("%.2lf", edge[i].w);
                break;
            }
            cnt++;
            parent[fx] = fy;
        }
    }
}
int main()
{
    input();
    build();
    kurs();
}