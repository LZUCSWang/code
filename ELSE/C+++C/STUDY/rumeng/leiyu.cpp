#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 1001
#define inf 2147483647
int vx[4] = {1, 0, -1, 0}, vy[4] = {0, 1, 0, -1};
int n, m, a, b, c;

int nums[MAX][MAX];
ll t, val[MAX][MAX], cnt;
ll head[MAX * MAX];  // cnt _max
int seen[MAX * MAX]; // 0 1
#define MAX_INF 9223372036854775807

ll idx;
ll dis[MAX * MAX][3];
struct node
{
    int to, w;
    ll nex;
} edges[MAX * 100000];
void add(int u, int v, int w)
{
    edges[++idx].to = v;
    edges[idx].w = w;
    edges[idx].nex = head[u];
    head[u] = idx;
}
typedef struct diji_node
{
    ll to, dis;
    bool operator<(diji_node q) const
    {
        return dis > q.dis;
    }
} diji_node;
inline void init(int flag)
{
    for (int i = 1; i <= cnt; i++)
    {
        dis[i][flag] = MAX_INF;
    }
    memset(seen, 0, sizeof(seen));
}
void diji(int start, int flag)
{
    priority_queue<diji_node> q;
    init(flag);
    dis[start][flag] = 0;
    q.push((diji_node){start, 0});
    while (!q.empty())
    {
        diji_node temp = q.top();
        q.pop();
        seen[temp.to] = 1;
        if (temp.dis != dis[temp.to][flag])
            continue;
        for (int i = head[temp.to]; i; i = edges[i].nex)
        {
            int to = edges[i].to;
            if (dis[to][flag] > temp.dis + edges[i].w)
            {
                dis[to][flag] = temp.dis + edges[i].w;
                if (!seen[to])
                    q.push((diji_node){to, dis[to][flag]});
            }
        }
    }
}
inline void input()
{
    cin >> n >> m >> a >> b >> c;
    for (int i = n; i; i--)
    {
        for (int j = 1; j <= m; j++)
        {
            scanf("%lld", &t);
            nums[i][j] = ++cnt;
            val[i][j] = t;
        }
    }
}
void build()
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                int ni = i + vx[k], nj = j + vy[k];
                if (ni >= 1 && ni <= n && nj >= 1 && nj <= m)
                {
                    add(nums[i][j], nums[ni][nj], val[ni][nj]);
                }
            }
        }
    }
}
ll ans = MAX_INF;
void work()
{
    diji(nums[n][a], 0);
    diji(nums[1][b], 1);
    diji(nums[1][c], 2);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            ans = min(ans, dis[nums[i][j]][0] + dis[nums[i][j]][1] + dis[nums[i][j]][2] - 2 * val[i][j]);
        }
    }
    printf("%lld", ans + val[n][a] + val[1][b] + val[1][c]);
}
int main()
{
    input();
    build();
    work();
}