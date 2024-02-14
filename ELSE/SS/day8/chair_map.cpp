#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
using namespace std;
#define MAX 2000005
int n, m, s, endss;
int idx, head[MAX];
int dis[MAX], vis[MAX], cost[MAX];
int pre[MAX], cnts[MAX];
int Time_ans, Distance_ans;
struct Node_of_quick_short
{
    int dis, tim, x;
    bool operator<(Node_of_quick_short p) const
    {
        if (tim == p.tim)
            return dis > p.dis;
        else
            return tim > p.tim;
    }
    Node_of_quick_short(int dis, int tim, int x) : dis(dis), tim(tim), x(x) {}
};
struct Node_of_short_lesscnt
{
    int dis, x;
    bool operator<(Node_of_short_lesscnt p) const
    {
        return dis > p.dis;
    }
    Node_of_short_lesscnt(int dis, int x) : dis(dis), x(x) {}
};
struct node
{
    int to, dis, cos, nex;
} edges[MAX];
void add(int a, int b, int c, int d)
{
    edges[++idx] = (node){b, c, d, head[a]};
    head[a] = idx;
}
stack<int> ans1, ans2;
void save_quick_short()
{
    int midd = endss;
    while (midd != s)
    {
        ans1.push(midd);
        midd = pre[midd];
    }
    ans1.push(s);
}
void save_short_lesscnt()
{
    int midd = endss;
    while (midd != s)
    {
        ans2.push(midd);
        midd = pre[midd];
    }
    ans2.push(s);
}
void inits()
{
    memset(dis, INF, sizeof(dis));
    memset(cost, INF, sizeof(cost));
    memset(vis, 0, sizeof(vis));
    memset(pre, 0, sizeof(pre));
    dis[s] = 0;  //起点距离为0
    cost[s] = 0; //起点花费为0
}
void dijkstra_quick_short()
{
    inits();
    priority_queue<Node_of_quick_short> q;
    q.push(Node_of_quick_short(0, 0, s));
    while (!q.empty())
    {
        Node_of_quick_short u = q.top();
        q.pop();

        if (vis[u.x]) //访问过则跳过
            continue;
        vis[u.x] = 1; //标记访问过

        for (int i = head[u.x]; i; i = edges[i].nex) //遍历该点所有邻接到的点
        {
            if (cost[edges[i].to] > edges[i].cos + cost[u.x]) //如果距离变短则更新
            {
                dis[edges[i].to] = dis[u.x] + edges[i].dis;
                cost[edges[i].to] = cost[u.x] + edges[i].cos;
                Node_of_quick_short v(dis[edges[i].to], cost[edges[i].to], edges[i].to);
                q.push(v);
                pre[edges[i].to] = u.x;
            }
            else if (cost[edges[i].to] == edges[i].cos + cost[u.x] && dis[edges[i].to] > dis[u.x] + edges[i].dis)
            {
                dis[edges[i].to] = dis[u.x] + edges[i].dis;
                pre[edges[i].to] = u.x;
            }
        }
    }
    // printf("%d\n", dis[endss]);
    Time_ans = cost[endss];
    save_quick_short();
}
void dijkstra_short_lesscnt()
{
    inits();
    priority_queue<Node_of_short_lesscnt> q;
    q.push(Node_of_short_lesscnt(dis[s], s));
    while (!q.empty())
    {
        Node_of_short_lesscnt u = q.top();
        q.pop();

        if (vis[u.x]) //访问过则跳过
            continue;
        vis[u.x] = 1; //标记访问过

        for (int i = head[u.x]; i; i = edges[i].nex) //遍历该点所有邻接到的点
        {
            if (dis[edges[i].to] > edges[i].dis + dis[u.x]) //如果距离变短则更新
            {
                dis[edges[i].to] = dis[u.x] + edges[i].dis;
                cost[edges[i].to] = cost[u.x] + edges[i].cos;
                q.push(Node_of_short_lesscnt(dis[edges[i].to], edges[i].to));
                pre[edges[i].to] = u.x;
                cnts[edges[i].to] = cnts[u.x] + 1;
            }
            else if (dis[edges[i].to] == edges[i].dis + dis[u.x] && cnts[edges[i].to] > cnts[u.x] + 1)
            {
                cnts[edges[i].to] = cnts[u.x] + 1;
                pre[edges[i].to] = u.x;
            }
        }
    }
    Distance_ans = dis[endss];
    save_short_lesscnt();
}
void print()
{

    if (ans1 == ans2)
    {
        printf("Time = %d; Distance = %d: ", Time_ans, Distance_ans);
        while (!ans1.empty())
        {
            printf("%d", ans1.top());
            if (ans1.size() > 1)
                printf(" => ");
            ans1.pop();
        }
    }
    else
    {
        // printf("Time = 6: 5 => 4 => 8 => 3\nDistance = 3: 5 => 1 => 3");
        printf("Time = %d: ", Time_ans);
        while (!ans1.empty())
        {
            printf("%d", ans1.top());
            if (ans1.size() > 1)
                printf(" => ");
            ans1.pop();
        }
        printf("\nDistance = %d: ", Distance_ans);
        while (!ans2.empty())
        {
            printf("%d", ans2.top());
            if (ans2.size() > 1)
                printf(" => ");
            ans2.pop();
        }
    }
}
void input()
{
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int a, b, c, d, e;
        scanf("%d%d%d%d%d", &a, &b, &c, &d, &e);
        add(a, b, d, e);
        if (c == 0)
            add(b, a, d, e);
    }
    cin >> s >> endss;
}
int main()
{
    input();
    dijkstra_quick_short();
    dijkstra_short_lesscnt();
    print();
    return 0;
}