// https://www.luogu.com.cn/problem/P1330
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 100050
queue<int> q;
int head[MAX], sum[3], flag[MAX], idx;
struct Node
{
    int to, nex;
} edge[MAX * 10];
void bfs(int s)
{
    q.push(s);
    sum[1] = sum[2] = 0;
    flag[s] = 1;
    sum[flag[s]]++;
    while (!q.empty())
    {
        int from = q.front();
        q.pop();
        for (int i = head[from]; i; i = edge[i].nex)
        {
            int to = edge[i].to;
            if (flag[to] == flag[from])
            {
                printf("Impossible");
                exit(0);
            }
            if (flag[to] == 0)
            {
                flag[to] = flag[from] % 2 + 1;
                sum[flag[to]]++;
                q.push(to);
            }
        }
    }
}
void add(int u, int v)
{
    edge[++idx] = (Node){v, head[u]};
    head[u] = idx;
}
int n, m;
void input()
{
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b);
        add(b, a);
    }
}
int ans;
int main()
{
    input();
    for (int i = 1; i <= n; i++)
        if (flag[i] == 0)
        {
            bfs(i);
            ans += min(sum[1], sum[2]);
        }
    cout << ans;
}