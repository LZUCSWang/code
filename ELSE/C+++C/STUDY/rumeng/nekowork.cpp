#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 100005
int n, k, s, l, dp[MAX];
vector<int> v[MAX];
int main()
{
    cin >> n >> k;
    while (k--)
        scanf("%d%d", &s, &l), v[s].push_back(l);
    for (int i = n; i; i--)
        if (v[i].empty())
            dp[i] = dp[i + 1] + 1;
        else
            for (int j = 0; j < v[i].size(); j++)
                dp[i] = max(dp[i], dp[i + v[i][j]]);
    cout << dp[1];
}