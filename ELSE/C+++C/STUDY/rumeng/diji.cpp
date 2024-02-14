#include <bits/stdc++.h>
using namespace std;
#define MAX 1000000
#define INF 2147483647
struct node
{
    int distance, to, inx;
} edges[MAX];
int indexs, head[MAX], n, m, s;
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
    cin >> n >> m >> s;
    for (int i = 1; i <= m; i++)
    {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        add(a, b, c);
    }
}
long long dis[MAX];
int vis[MAX];
void diji()
{
    priority_queue<Node> q;
    Node st;
    for (int i = 1; i <= n; i++)
    {
        dis[i] = INF;
    }
    st.dis = 0;
    dis[s] = 0;
    st.to = s;
    q.push(st);
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
                Node t;
                t.to = edges[i].to;
                t.dis = dis[edges[i].to];
                q.push(t);
            }
        }
    }
}

int main()
{
    input();
    diji();
    for (int i = 1; i <= n; i++)
    {
        printf("%lld ", dis[i]);
    }
}