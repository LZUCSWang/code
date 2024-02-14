#include <bits/stdc++.h>
using namespace std;
#define MAX 100005
int dp[MAX];
int main()
{
    memset(dp, 0, sizeof(dp));
    int n, k;
    cin >> n >> k;
    dp[1] = 1;
    dp[0] = 1;
    for (int i = 2; i <= n; i++)
    {
        for (int j = 1; j <= k && j <= i; j++)
        {
            dp[i] += (dp[i - j]) % 100003;
        }
        dp[i] %= 100003;
    }
    // for (int i = 1; i <= n; i++)
    // {
    //     cout << dp[i] << " ";
    // }
    // cout << endl;
    cout << dp[n] << endl;
    return 0;
}