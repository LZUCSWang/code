#include <bits/stdc++.h>
using namespace std;
#define INF 2e9
#define MAX 100000
#define ri register int
// https://www.luogu.com.cn/problem/P2341
int head[MAX], idx;
struct Node
{
    int from, to, nex;
} edge[MAX * 10];
inline void add(int u, int v)
{
    edge[++idx].to = v;
    edge[idx].from = u;
    edge[idx].nex = head[u];
    head[u] = idx;
}

int dfn[MAX], low[MAX], tim, cnt, belong[MAX], nums[MAX], top;
bool vis[MAX];
int s[MAX];
void tarjan(int now)
{
    dfn[now] = low[now] = ++tim;
    vis[now] = true;
    s[++top] = now;
    for (int i = head[now]; i; i = edge[i].nex)
    {
        int to = edge[i].to;
        if (!dfn[to])
        {
            tarjan(to);
            low[now] = min(low[now], low[to]);
        }
        else if (vis[to])
        {
            low[now] = min(low[now], dfn[to]);
        }
    }
    if (dfn[now] == low[now])
    {
        belong[now] = ++cnt;
        nums[cnt]++;
        vis[now] = false;
        while (s[top] != now)
        {
            vis[s[top]] = false;
            belong[s[top]] = cnt;
            nums[cnt]++;
            top--;
        }
        top--;
    }
}
int n, m, dutt[MAX];

inline void in(int &read)
{
    int x = 0, f = 1;
    char ch;
    for (ch = getchar(); (ch < '0' || ch > '9') && ch != '-'; ch = getchar())
        ;
    if (ch == '-')
    {
        f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = (x << 3) + (x << 1) + ch - '0';
        ch = getchar();
    }
    read = x * f; //可以处理负数的读入优化
}
inline void input()
{
    in(n);
    in(m);
    int a, b;
    for (ri i = 1; i <= m; i++)
    {
        in(a), in(b);
        add(a, b);
    }
}
int main()
{
    input();
    for (ri i = 1; i <= n; i++)
    {
        if (!dfn[i])
            tarjan(i);
    }
    for (int i = 1; i <= m; i++)
    {
        if (belong[edge[i].from] != belong[edge[i].to])
        {
            dutt[belong[edge[i].from]]++;
        }
    }
    int ans = 0;
    for (ri i = 1; i <= cnt; i++)
    {
        if (!dutt[i])
        {

            if (ans)
            {
                printf("0");
                return 0;
            }
            ans = i;
        }
    }
    printf("%d", nums[ans]);
}