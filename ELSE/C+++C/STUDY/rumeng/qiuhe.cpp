#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 10000000
#define ll long long
#define mod 10007

int color[MAX], nums[MAX], cnt[MAX][2], sum[MAX][2];
int n, m;
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        scanf("%d", nums + i);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", color + i);
        cnt[color[i]][i & 1]++;
        sum[color[i]][i & 1] = (sum[color[i]][i & 1] + nums[i]) % mod;
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans = (ans + i * ((cnt[color[i]][i & 1] - 2) * nums[i] % mod + sum[color[i]][i & 1])) % mod;
    printf("%d", ans);
}