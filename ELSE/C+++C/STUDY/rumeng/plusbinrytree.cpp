#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 40
#define ll long long

ll n, v[MAX], dp[MAX][MAX], root[MAX][MAX];
void order(int left, int right)
{
    if (right >= left)
        printf("%lld ", root[left][right]);
    if (right < left || right == left)
        return;
    order(left, root[left][right] - 1);
    order(root[left][right] + 1, right);
}
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &dp[i][i]);
        dp[i][i - 1] = 1, root[i][i] = i;
    }
    for (int step = 1; step <= n; step++)
        for (int left = 1, right = left + step; right <= n; left++, right++)
        {
            dp[left][right] = v[left] + dp[left + 1][right], root[left][right] = left;
            for (int k = left; k < right; k++)
            {
                if (dp[left][right] < dp[left][k - 1] * dp[k + 1][right] + dp[k][k])
                {
                    dp[left][right] = dp[left][k - 1] * dp[k + 1][right] + dp[k][k];
                    root[left][right] = k;
                }
            }
        }
    printf("%lld\n", dp[1][n]);
    order(1, n);
}
