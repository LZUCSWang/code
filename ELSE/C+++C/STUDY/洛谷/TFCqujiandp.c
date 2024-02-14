#include <stdio.h>
int main()
{
    int n;
    scanf("%d", &n);
    int data[n + 1];
    int dp[n + 1][n + 1];
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &data[i]);
        dp[i][i] = data[i] * n;
    }
    for (int jiange = 2; jiange <= n; jiange++)
    {
        for (int l = 1; l <= n - jiange + 1; l++)
        {
            int r = l + jiange - 1;
            int datas = dp[l][r - 1] + data[r] * (n + jiange - 1), b = dp[l + 1][r] + data[l] * (n + jiange - 1);
            dp[l][r] = datas > b ? datas : b;
        }
    }
    printf("%d", dp[1][n]);
}