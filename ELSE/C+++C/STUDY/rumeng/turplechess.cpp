#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 50

int n, m;
int dp[MAX][MAX][MAX][MAX], value[MAX * 100], nums[5];
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        scanf("%d", value + i);
    for (int i = 1, t; i <= m; i++)
    {
        scanf("%d", &t);
        nums[t]++;
    }
    dp[0][0][0][0] = value[1];
    for (int a = 0; a <= nums[1]; a++)
        for (int b = 0; b <= nums[2]; b++)
            for (int c = 0; c <= nums[3]; c++)
                for (int d = 0; d <= nums[4]; d++)
                {
                    int pos = 1 + a + b * 2 + c * 3 + d * 4;
                    if (a)
                        dp[a][b][c][d] = max(dp[a - 1][b][c][d] + value[pos], dp[a][b][c][d]);
                    if (b)
                        dp[a][b][c][d] = max(dp[a][b - 1][c][d] + value[pos], dp[a][b][c][d]);
                    if (c)
                        dp[a][b][c][d] = max(dp[a][b][c - 1][d] + value[pos], dp[a][b][c][d]);
                    if (d)
                        dp[a][b][c][d] = max(dp[a][b][c][d - 1] + value[pos], dp[a][b][c][d]);
                }
    printf("%d", dp[nums[1]][nums[2]][nums[3]][nums[4]]);
}