#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
using namespace std;
#define MAX 2000005
int n, m, s, endss;
int idx, e[MAX], w[MAX], h[MAX], ne[MAX], vv[MAX];
int dis[MAX], vis[MAX], cost[MAX];

struct Node
{
    int dis, val, x;
    bool operator<(Node p) const
    {
        if (dis == p.dis)
            return val > p.val;
        else
            return dis > p.dis;
    }
    Node(int dis, int val, int x) : dis(dis), val(val), x(x) {}
};

void add(int a, int b, int c, int d)
{
    e[++idx] = b;
    w[idx] = c;
    vv[idx] = d;
    ne[idx] = h[a];
    h[a] = idx;
}

void dijkstra()
{
    memset(dis, INF, sizeof(dis));
    priority_queue<Node> q;
    dis[s] = 0;  //起点距离为0
    cost[s] = 0; //起点花费为0
    q.push(Node(dis[s], cost[s], s));
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
                cost[e[i]] = cost[u.x] + vv[i];
                Node v(dis[e[i]], cost[e[i]], e[i]);
                q.push(v);
            }
            else if (dis[e[i]] == dis[u.x] + w[i] && cost[e[i]] > vv[i] + cost[u.x])
            {
                cost[e[i]] = cost[u.x] + vv[i];
                Node v(dis[e[i]], cost[e[i]], e[i]);
                q.push(v);
            }
        }
    }
}

int main()
{
    cin >> n >> m >> s >> endss;
    for (int i = 1; i <= m; i++)
    {
        int a, b, c, d;
        scanf("%d %d %d %d", &a, &b, &c, &d);
        add(a, b, c, d);
        add(b, a, c, d);
    }

    dijkstra();

    cout << dis[endss] << ' ' << cost[endss] << endl;
    return 0;
}