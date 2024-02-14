#include <bits/stdc++.h>
using namespace std;
#define MAX 10000
#define INF 2147483647
struct node
{
    int distance, to, inx;
} edges[MAX];
int indexs, head[MAX];
int N, P, C;
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
int place[MAX];
void input()
{
    cin >> N >> P >> C;
    for (int i = 1; i <= N; i++)
        scanf("%d", place + i);
    for (int i = 1, a, b, c; i <= C; i++)
    {
        scanf("%d %d %d", &a, &b, &c);
        add(a, b, c);
        add(b, a, c);
    }
}
int dis[MAX], vis[MAX];
void diji(int start)
{
    priority_queue<Node> q;
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= P; i++)
        dis[i] = INF;
    dis[start] = 0;
    q.push(Node{start, 0});
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
                q.push(Node{edges[i].to, dis[edges[i].to]});
            }
        }
    }
}

long long ans, minans = 2e9;
int main()
{
    input();
    for (int i = 1; i <= P; i++)
    {
        diji(i);
        ans = 0;
        for (int i = 1; i <= N; i++)
            ans += dis[place[i]];
        minans = min(minans, ans);
    }
    printf("%lld", minans);
}