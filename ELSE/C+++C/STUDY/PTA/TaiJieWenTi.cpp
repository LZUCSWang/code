#include <bits/stdc++.h>
using namespace std;
#define MAXN 100005
int dp[MAXN];
int N, K, ans;

int main()
{
    ios::sync_with_stdio(false);
    cin >> N >> K;
    dp[0] = 1;
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= K; j++)
        {
            if (i - j >= 0)
            {
                dp[i] = (dp[i] + dp[i - j]) % 100003;
            }
        }
    }
    cout << dp[N] << endl;
}