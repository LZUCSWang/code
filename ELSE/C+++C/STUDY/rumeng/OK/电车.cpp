// https://www.luogu.com.cn/problem/P1346
#include <bits/stdc++.h>
using namespace std;
#define MAX 1000000
#define INF 2147483647
struct node
{
    int distance, to, inx;
} edges[MAX * 10];
int indexs, head[MAX], n, m, s, e;
typedef struct Node
{
    int to, dis;
    bool operator<(Node p) const
    {
        return dis > p.dis;
    }
} Node;
void add(int from, int to, int distance)
{
    edges[++indexs].to = to;
    edges[indexs].distance = distance;
    edges[indexs].inx = head[from];
    head[from] = indexs;
}
void input()
{
    cin >> n >> s >> e;
    int v;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &m);
        for (int j = 1; j <= m; j++)
        {
            scanf("%d", &v);
            if (j == 1)
            {
                add(i, v, 0);
            }
            else
            {
                add(i, v, 1);
            }
        }
    }
}
long long dis[MAX];
int vis[MAX];
void diji()
{
    priority_queue<Node> q;
    for (int i = 1; i <= n; i++)
    {
        dis[i] = INF;
    }
    dis[s] = 0;
    q.push((Node){s, 0});
    while (!q.empty())
    {
        Node temp = q.top();
        q.pop();
        if (vis[temp.to])
            continue;
        vis[temp.to] = 1;
        for (int i = head[temp.to]; i; i = edges[i].inx)
        {
            if (dis[edges[i].to] > temp.dis + edges[i].distance)
            {
                dis[edges[i].to] = temp.dis + edges[i].distance;
                if (!vis[edges[i].to])
                {
                    q.push((Node){edges[i].to, dis[edges[i].to]});
                }
            }
        }
    }
}

int main()
{
    input();
    diji();
    if (dis[e] == INF)
        printf("-1");
    else
        printf("%lld", dis[e]);
}