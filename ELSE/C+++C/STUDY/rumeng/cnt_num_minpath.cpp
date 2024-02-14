#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 1000001
vector<int> G[MAX];
int n, m, x, y;
void input()
{
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &x, &y);
        G[x].push_back(y);
        G[y].push_back(x);
    }
}
int seen[MAX];
int ans[MAX];
int depth[MAX];
#define MOD 100003
void bfs()
{
    queue<int> q;
    q.push(1);
    ans[1] = 1;
    seen[1] = 1;
    while (!q.empty())
    {
        int now = q.front();
        q.pop();
        for (int i = 0; i < G[now].size(); i++)
        {
            int to = G[now][i];
            if (!seen[to])
            {
                seen[to] = 1;
                q.push(to);
                depth[to] = depth[now] + 1;
            }
            if (depth[to] == depth[now] + 1)
            {
                ans[to] = (ans[to] + ans[now]) % MOD;
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        printf("%d\n", ans[i]);
    }
}
int main()
{
    input();
    bfs();
}