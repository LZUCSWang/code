// https://www.luogu.com.cn/problem/P3385
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 1000001
// 2
// 3 4
// 1 2 2
// 1 3 4
// 2 3 1
// 3 1 -3
// 3 3
// 1 2 3
// 2 3 4
// 3 1 -8
struct Node
{
    int to, w, nex;
} edge[MAX];
int head[MAX], idx;
int n, m;
void add(int u, int v, int w)
{
    edge[++idx] = (Node){v, w, head[u]};
    head[u] = idx;
}
void input()
{
    cin >> n >> m;
    while (m--)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        if (c >= 0)
            add(b, a, c);
        add(a, b, c);
    }
}
int vis[MAX], dis[MAX], cnt[MAX];
queue<int> q;
void spfa()
{
    while (!q.empty())
        q.pop();
    q.push(1);
    vis[1] = 1;
    dis[1] = 0;
    while (!q.empty())
    {
        int x = q.front();
        q.pop();
        vis[x] = 0;
        for (int i = head[x]; i; i = edge[i].nex)
        {
            int y = edge[i].to;
            if (dis[y] > dis[x] + edge[i].w)
            {
                dis[y] = dis[x] + edge[i].w;
                if (vis[y] == 0)
                {
                    vis[y] = 1;
                    cnt[y]++;
                    if (cnt[y] == n)
                    {
                        cout << "YES" << endl;
                        return;
                    }
                    q.push(y);
                }
            }
        }
    }
    cout << "NO" << endl;
}
void init()
{
    memset(edge, 0, sizeof(edge));
    memset(vis, 0, sizeof(vis));
    memset(dis, 1000000, sizeof(dis));
    memset(cnt, 0, sizeof(cnt));
    idx = 0;
    memset(head, 0, sizeof(head));
}
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        init();
        input();
        spfa();
    }
}