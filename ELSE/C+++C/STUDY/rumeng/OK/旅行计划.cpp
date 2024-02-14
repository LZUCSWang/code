// 5 6
// 1 2
// 1 3
// 2 3
// 2 4
// 3 4
// 2 5

#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 10000000
// https://www.luogu.com.cn/problem/P1137
int head[MAX], idx;
struct Node
{
    int to, nex;
} edge[MAX];
void add(int u, int v)
{
    edge[++idx] = Node{v, head[u]};
    head[u] = idx;
}
int n, m, dutt[MAX];

void input()
{
    cin >> n >> m;
    for (int i = 1, a, b; i <= m; i++)
    {
        scanf("%d%d", &a, &b);
        add(a, b);
        dutt[b]++;
    }
}

queue<int> q;
int tp[MAX], k;
void tupo()
{
    for (int i = 1; i <= n; i++)
    {
        if (dutt[i] == 0)
        {
            tp[++k] = i;
            q.push(i);
        }
    }
    while (!q.empty())
    {
        int now = q.front();
        q.pop();
        for (int i = head[now]; i; i = edge[i].nex)
        {
            int to = edge[i].to;
            if (dutt[to])
            {
                dutt[to]--;
                if (dutt[to] == 0)
                {
                    tp[++k] = to;
                    q.push(to);
                }
            }
        }
    }
}
int dp[MAX];
void dpp()
{
    for (int i = 1; i <= n; i++)
    {
        dp[i] = 1;
    }
    for (int i = 1; i <= k; i++)
    {
        int now = tp[i];
        for (int j = head[now]; j; j = edge[j].nex)
        {
            int to = edge[j].to;
            dp[to] = max(dp[to], dp[now] + 1);
        }
    }
    for (int i = 1; i <= n; i++)
    {
        printf("%d\n", dp[i]);
    }
}
int main()
{
    input();
    tupo();
    dpp();
}