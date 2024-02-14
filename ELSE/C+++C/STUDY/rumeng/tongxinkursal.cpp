#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 10000001
int s, p;
struct point
{
    int x, y;
} edges[MAX];
struct Node
{
    int u, v, w;
} Edges[MAX];
int idx;
void input()
{
    scanf("%d%d", &s, &p);
    for (int i = 1; i <= p; i++)
    {
        scanf("%d%d", &edges[i].x, &edges[i].y);
    }
}
bool cmp(Node a, Node b)
{
    return a.w < b.w;
}
void buile_edges()
{
    for (int i = 1; i < p; i++)
    {
        for (int j = i + 1; j <= p; j++)
        {
            Edges[++idx].u = i;
            Edges[idx].v = j;
            Edges[idx].w = pow(edges[i].x - edges[j].x, 2) + pow(edges[i].y - edges[j].y, 2);
        }
    }
    sort(Edges + 1, Edges + idx + 1, cmp);
}
int parent[MAX];
int fa(int x)
{
    return (x == parent[x]) ? x : parent[x] = fa(parent[x]);
}
void init()
{
    for (int i = 1; i <= p; i++)
    {
        parent[i] = i;
    }
}
void kuraskl()
{
    for (int i = 1; i <= idx; i++)
    {
        int fx = fa(Edges[i].u), fy = fa(Edges[i].v);
        if (fx != fy)
        {
            parent[fx] = fy;
            s++;
            if (s == p)
            {
                printf("%.2lf", sqrt(Edges[i].w));
                exit(0);
            }
        }
    }
}
int main()
{
    input();
    buile_edges();
    init();
    kuraskl();
}