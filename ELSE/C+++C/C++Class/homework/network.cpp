#include <bits/stdc++.h>
using namespace std;
#define INF 2e9
#define MAX 30
int M, N, K;
int main()
{
    vector<vector<int>> times;
    scanf("%d %d %d", &M, &N, &K);
    for (int i = 0; i < M; i++)
    {
        vector<int> temp;
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        temp.push_back(a);
        temp.push_back(b);
        temp.push_back(c);
        times.push_back(temp);
    }
    long long dp[N + 1][N + 1];
    bool vis[N + 1] = {false};
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            if (j == i)
                dp[i][j] = 0;
            else
                dp[i][j] = INT_MAX;
    for (int i = 0; i < times.size(); i++)
        dp[times[i][0]][times[i][1]] = times[i][2];
    vis[K] = true;
    for (int i = 1; i < N; i++)
    {
        int minidx = 0, mindis = INT_MAX;
        for (int j = 1; j <= N; j++)
        {
            if (!vis[j] && mindis > dp[K][j])
            {
                mindis = dp[K][j];
                minidx = j;
            }
        }
        vis[minidx] = true;
        for (int j = 1; j <= N; j++)
            if (dp[K][minidx] + dp[minidx][j] < dp[K][j])
                dp[K][j] = dp[K][minidx] + dp[minidx][j];
    }
    int m = 0;
    for (int i = 1; i <= N; i++)
        if (m < dp[K][i])
            m = dp[K][i];
    printf("%d", m == INT_MAX ? -1 : m);
}
