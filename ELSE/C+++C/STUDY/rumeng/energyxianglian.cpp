#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 1005

int dp[MAX][MAX], v[MAX];
int n;
void input()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", v + i);
        v[i + n] = v[i];
    }
}

int main()
{
    input();
    for (int step = 2; step <= n; step++)
    {
        for (int left = 1, right = left + step; right <= n * 2; left++, right++)
        {
            for (int k = left + 1; k <= right - 1; k++)
            {
                dp[left][right] = max(dp[left][right], dp[left][k] + dp[k][right] + v[left] * v[right] * v[k]);
            }
        }
    }
    int maxx = 0;
    for (int i = 1; i <= n; i++)
    {
        maxx = max(maxx, dp[i][i + n]);
    }
    printf("%d", maxx);
}