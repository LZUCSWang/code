#include <bits/stdc++.h>
using namespace std;
#define MAX 505
int adj[MAX][MAX];
// 7 8
// 7 6
// 7 4
// 6 5
// 4 1
// 5 2
// 5 3
// 2 1
// 3 1
// 7 1
int n, m;
int s, e;
int value[MAX], visits[MAX];
int dfs(int from)
{
    visits[from] = 1;
    if (value[from])
        return value[from];
    for (int to = 1; to <= n; to++)
    {
        if (adj[from][to])
        {
            value[from] += dfs(to);
        }
    }
    return value[from];
}
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a][b] = 1;
    }
    cin >> s >> e;
    value[e] = 1;
    int cnt = dfs(s);
    cout << cnt << " ";
    for (int i = 1; i <= n; i++)
    {
        if (visits[i] && value[i] == 0)
        {
            printf("No\n");
            return 0;
        }
    }
    printf("Yes\n");
}