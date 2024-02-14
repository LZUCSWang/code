#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 10000050
// https://www.luogu.com.cn/problem/P1073
int head[MAX], idx;
struct Node
{
    int from, to, nex;
} edge[MAX];

void add(int u, int v)
{
    edge[++idx] = Node{u, v, head[u]};
    head[u] = idx;
}

int min_o[MAX], min_s[MAX], max_o[MAX], max_s[MAX];
int n, m;
int val[MAX];
int x[MAX], y[MAX];
void input()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        scanf("%d", val + i);
    int j = m;
    for (int i = 1, c; i <= m; i++)
    {
        scanf("%d%d%d", x + i, y + i, &c);
        add(x[i], y[i]);
        if (c == 2)
        {
            add(y[i], x[i]);
            j++;
            x[j] = y[i];
            y[j] = x[i];
        }
    }
    m = j;
    for (int i = 1; i <= n; i++)
    {
        min_s[i] = INF;
    }
}

int dfn[MAX], low[MAX], tim, belong[MAX], cnt;
bool vis[MAX];
stack<int> s;

void tarjan(int now)
{
    dfn[now] = low[now] = ++tim;
    vis[now] = true;
    s.push(now);
    for (int i = head[now]; i; i = edge[i].nex)
    {
        int to = edge[i].to;
        if (!dfn[to])
        {
            tarjan(to);
            low[now] = min(low[to], low[now]);
        }
        else if (vis[to])
            low[now] = min(low[now], dfn[to]);
    }
    if (dfn[now] == low[now])
    {
        cnt++;
        min_s[cnt] = min(min_s[cnt], val[now]);
        max_s[cnt] = max(max_s[cnt], val[now]);
        vis[now] = false;
        belong[now] = cnt;
        while (s.top() != now)
        {
            int top = s.top();
            belong[top] = cnt;
            vis[top] = false;
            min_s[cnt] = min(min_s[cnt], val[top]);
            max_s[cnt] = max(max_s[cnt], val[top]);
            s.pop();
        }
        s.pop();
    }
}

int dutt[MAX], dp[MAX];
queue<int> q;

void tupo()
{
    int belong1 = belong[1];
    vis[belong1] = true;
    dp[belong1] = max_s[belong1] - min_s[belong1];
    for (int i = 1; i <= cnt; i++)
        if (!dutt[i])
            q.push(i);
    while (!q.empty())
    {
        int now = q.front();
        q.pop();
        for (int i = head[now]; i; i = edge[i].nex)
        {
            int to = edge[i].to;
            dutt[to]--;
            if (vis[now])
            {
                min_s[to] = min(min_s[to], min_s[now]);
                dp[to] = max(dp[to], max(dp[now], max_s[to] - min_s[to]));
                vis[to] = true;
            }
            if (!dutt[to])
                q.push(to);
        }
    }
    printf("%d", dp[belong[n]]);
}

void rebuild()
{
    memset(head, 0, sizeof(head));
    memset(vis, 0, sizeof(vis));
    idx = 0;
    for (int i = 1; i <= m; i++)
        if (belong[x[i]] != belong[y[i]])
        {
            add(belong[x[i]], belong[y[i]]);
            dutt[belong[y[i]]]++;
        }
}
int main()
{
    input();
    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            tarjan(i);
    rebuild();
    tupo();
}