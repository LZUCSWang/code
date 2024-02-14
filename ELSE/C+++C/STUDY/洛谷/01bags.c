#include <stdio.h>
#include <string.h>
int main()
{
    long long int n, m;
    scanf("%lld %lld", &n, &m);
    long long int w[n], v[n];
    long long int dp[m + 1];
    memset(dp, 0, sizeof(long long int) * (m + 1));
    for (long long int i = 0; i < n; i++)
    {
        scanf("%lld %lld", &w[i], &v[i]);
    }
    for (long long int i = 0; i < n; i++)
    {
        for (long long int j = m; j >= w[i]; j--)
        {
            dp[j] = dp[j] > (dp[j - w[i]] + v[i]) ? dp[j] : dp[j - w[i]] + v[i];
        }
    }
    printf("%lld", dp[m]);
}
