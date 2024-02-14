#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 10000
int place_color[MAX], color_idx[MAX];
vector<int> conflict[MAX];
int head[MAX], idx;
struct Node
{
    int to, dis, nex;
} edge[MAX];
void add(int u, int v, int dis)
{
    edge[++idx] = Node{v, dis, head[u]};
    head[u] = idx;
}
int ans;
set<int> have;
int n, k, m, s, t;
void dfs(int now, int dis)
{
    if (dis > ans)
        return;
    if (now == t)
    {
        ans = min(ans, dis);
        return;
    }
    for (int i = head[now]; i; i = edge[i].nex)
    {
        int to = edge[i].to;
        bool flag_ = false;
        for (int j = 0; j < conflict[color_idx[to]].size(); j++)
        {
            if (have.find(conflict[color_idx[to]][j]) != have.end())
            {
                flag_ = true;
                break;
            }
        }
        if (!flag_ && !place_color[color_idx[to]])
        {
            place_color[color_idx[to]] = 1;
            have.insert(color_idx[to]);
            dfs(to, dis + edge[i].dis);
            place_color[color_idx[to]] = 0;
            have.erase(color_idx[to]);
        }
    }
}
void input()
{
    cin >> n >> k >> m >> t >> s;
    for (int i = 1; i <= n; i++)
        scanf("%d", color_idx + i);
    for (int i = 1; i <= k; i++)
    {
        for (int j = 1, tt; j <= k; j++)
        {
            scanf("%d", &tt);
            if (tt)
                conflict[j].push_back(i);
        }
    }
    for (int i = 1, u, v, d; i <= m; i++)
    {
        scanf("%d%d%d", &u, &v, &d);
        add(u, v, d);
        add(v, u, d);
    }
}
int main()
{
    input();
    ans = INF;
    have.insert(color_idx[s]);
    place_color[color_idx[s]] = 1;
    dfs(s, 0);
    (ans < INF) ? printf("%d", ans) : printf("-1");
}