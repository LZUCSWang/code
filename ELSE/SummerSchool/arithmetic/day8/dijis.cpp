#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
using namespace std;
#define MAX 2000005
int n, m, s, endss;
int idx, e[MAX], w[MAX], h[MAX], ne[MAX];
int dis[MAX], vis[MAX];

struct Node
{
    int dis, x;
    bool operator<(Node p) const
    {
        return dis > p.dis;
    }
    Node(int dis, int x) : dis(dis), x(x) {}
};

void add(int a, int b, int c)
{
    e[++idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx;
}

void dijkstra()
{
    memset(dis, INF, sizeof(dis));
    priority_queue<Node> q;
    dis[s] = 0; //起点距离为0
    Node u(dis[s], s);
    q.push(u);
    while (!q.empty())
    {
        Node u = q.top();
        q.pop();

        if (vis[u.x]) //访问过则跳过
            continue;
        vis[u.x] = 1; //标记访问过

        for (int i = h[u.x]; i; i = ne[i]) //遍历该点所有邻接到的点
        {
            if (dis[e[i]] > dis[u.x] + w[i]) //如果距离变短则更新
            {
                dis[e[i]] = dis[u.x] + w[i];
                Node v(dis[e[i]], e[i]);
                q.push(v);
            }
        }
    }
}

int main()
{
    cin >> n >> m;
    s = 0;
    for (int i = 1; i <= m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
        // add(b, a, c);
    }

    dijkstra();

    for (int i = 1; i <= n; i++)
    {
        if (dis[i] != INF)
            cout << dis[i] << " ";
    }
    return 0;
}