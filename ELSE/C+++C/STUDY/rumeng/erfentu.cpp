#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 10000001

vector<int> G[MAX];
int match[MAX], vis[MAX];
bool dfs(int u, int flag)
{
    if (vis[u] == flag)
        return false;
    vis[u] = flag;
    for (int v : G[u])
        if (!match[v] || dfs(match[v], flag))
        {
            match[v] = u;
            return true;
        }
    return false;
}
int n, m, t, a, b, ans;
int main()
{
    cin >> n >> m >> t;
    for (int i = 1; i <= t; i++)
    {
        scanf("%d%d", &a, &b);
        G[a].push_back(b);
    }
    for (int i = 1; i <= n; i++)
    {
        if (dfs(i, i))
            ans++;
    }
    printf("%d", ans);
}