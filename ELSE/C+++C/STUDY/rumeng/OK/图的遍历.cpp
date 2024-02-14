// https://www.luogu.com.cn/problem/P3916#submit
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 100005

stack<int> S;
int idx, head[MAX], instack[MAX], low[MAX], DFN[MAX], tim, cnt, M[MAX], belong[MAX], ans[MAX], n, m, x[MAX], y[MAX];
struct Node
{
    int to, nex;
} edge[MAX];
void add(int u, int v)
{
    edge[++idx] = (Node){v, head[u]};
    head[u] = idx;
}
void tarjan(int s)
{
    S.push(s);
    instack[s] = 1;
    low[s] = DFN[s] = tim++;
    for (int i = head[s]; i; i = edge[i].nex)
    {
        int to = edge[i].to;
        if (!DFN[to])
        {
            tarjan(to);
            low[s] = min(low[s], low[to]);
        }
        else if (instack[to])
            low[s] = min(low[s], DFN[to]);
    }
    if (low[s] == DFN[s])
    {
        cnt++;
        while (true)
        {
            int t = S.top();
            S.pop();
            belong[t] = cnt;
            instack[t] = 0;
            M[cnt] = max(M[cnt], t);
            if (t == s)
            {
                break;
            }
        }
    }
}
void dfs(int x)
{
    ans[x] = M[x];
    for (int i = head[x]; i; i = edge[i].nex)
    {
        int to = edge[i].to;
        if (!ans[to])
            dfs(to);
        ans[x] = max(ans[x], ans[to]);
    }
}
void input()
{
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", x + i, y + i);
        add(x[i], y[i]);
    }
}
void init()
{
    memset(head, 0, sizeof(head));
    memset(edge, 0, sizeof(edge));
    idx = 0;
}
void rebuild()
{
    init();
    for (int i = 1; i <= m; i++)
    {
        if (belong[x[i]] != belong[y[i]])
            add(belong[x[i]], belong[y[i]]);
    }
}
int main()
{
    input();
    for (int i = 1; i <= n; i++)
    {
        if (!DFN[i])
            tarjan(i);
    }
    rebuild();
    for (int i = 1; i <= cnt; i++)
    {
        if (!ans[i])
            dfs(i);
    }
    for (int i = 1; i <= n; i++)
    {
        printf("%d ", ans[belong[i]]);
    }
}