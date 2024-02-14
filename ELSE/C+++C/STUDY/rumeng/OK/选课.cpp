#include <bits/stdc++.h>
// https://www.luogu.com.cn/problem/P2014
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 1000
// 7  4
// 2  2
// 0  1
// 0  4
// 2  1
// 7  1
// 7  6
// 2  2
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
int dp[MAX][MAX];
int n, m;
void input()
{
    cin >> n >> m;
    for (int i = 1, fa; i <= n; i++)
    {
        scanf("%d%d", &fa, &dp[i][1]);
        add(fa, i);
        // add(0, i);
    }
    m++;
}

void dpp(int now)
{
    for (int i = head[now]; i; i = edge[i].nex)
    {
        int to = edge[i].to;
        dpp(to);
        for (int j = m; j > 0; j--)
            for (int k = 0; k < j; k++)
                dp[now][j] = max(dp[now][j], dp[now][j - k] + dp[to][k]);
    }
}
int main()
{
    input();
    dpp(0);
    printf("%d",dp[0][m]);
}