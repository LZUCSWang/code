#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 1000
// https://www.luogu.com.cn/problem/P2015
int head[MAX], idx;
struct Node
{
    int to, w, nex;
} edge[MAX];
void add(int u, int v, int w)
{
    edge[++idx] = Node{v, w, head[u]};
    head[u] = idx;
}
int n, m;
int dp[MAX][MAX];
// 5 2
// 1 3 1
// 1 4 10
// 2 3 20
// 3 5 20

void input()
{
    cin >> n >> m;
    for (int i = 1, u, v, w; i <= n - 1; i++)
    {
        scanf("%d%d%d", &u, &v, &w);
        add(u, v, w);
        add(v, u, w);
    }
}
int vis[MAX];
void dfs(int root)
{
    vis[root] = 1;
    for (int i = head[root]; i; i = edge[i].nex)
    {
        int to = edge[i].to;
        if (!vis[to])
        {
            dfs(to);
            for (int j = m; j; j--)
            {
                for (int k = 0; k < j; k++)
                {
                    dp[root][j] = max(dp[root][j], dp[root][j - k - 1] + dp[to][k] + edge[i].w);
                }
            }
        }
    }
}
int main()
{
    input();
    dfs(1);
    printf("%d", dp[1][m]);
    return 0;
}