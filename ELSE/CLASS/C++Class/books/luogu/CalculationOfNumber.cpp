#include <bits/stdc++.h>
using namespace std;
int orign;
int main()
{
    cin >> orign;
    int dp[orign+1] = {0};
    for (int i = 1; i <= orign; i++)
    {
        for (int j = 1; j <= i / 2; j++)
            dp[i] += dp[j];
        dp[i]++;
    }
    cout << dp[orign];
    return 0;
}