#include <bits/stdc++.h>
using namespace std;
#define MAX 10000000
#define INF 2147483647
double dis[MAX];
int vis[MAX];
struct node
{
    int to, inx;
    double distance;
} edges[MAX];
int indexs, head[MAX], n, m, s, e;
typedef struct Node
{
    int to;
    double dis;
    bool operator<(Node p) const
    {
        return dis > p.dis;
    }
} Node;
void add(int from, int to, double distance)
{
    edges[++indexs].to = to;
    edges[indexs].distance = distance;
    edges[indexs].inx = head[from];
    head[from] = indexs;
}
void input()
{
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        add(a, b, 1 - c * 1.0 / 100);
        add(b, a, 1 - c * 1.0 / 100);
    }
    cin >> e >> s;
}
void diji()
{
    priority_queue<Node> q;
    for (int i = 1; i <= n; i++)
    {
        dis[i] = INF;
    }
    dis[s] = 100;
    q.push((Node){s, 100});
    while (!q.empty())
    {
        Node temp = q.top();
        q.pop();
        if (vis[temp.to])
            continue;
        vis[temp.to] = 1;
        for (int i = head[temp.to]; i; i = edges[i].inx)
        {
            int to = edges[i].to;
            if (dis[to] > (double)temp.dis / (edges[i].distance))
            {
                dis[to] = (double)temp.dis / edges[i].distance;
                q.push((Node){to, dis[to]});
            }
        }
    }
}

int main()
{
    input();
    diji();
    printf("%.8lf", dis[e]);
}