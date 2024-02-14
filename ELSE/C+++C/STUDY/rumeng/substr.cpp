// 6 3 1
// aabaab
// aab

#include <bits/stdc++.h>
using namespace std;
#define mod 1000000007
#define INF 2e9
#define MAX 1005

char A[MAX], B[MAX];
int n, m, p;
int dp[2][MAX][MAX][2];

int main()
{
    cin >> n >> m >> p;
    scanf("%s", A + 1);
    scanf("%s", B + 1);
    dp[0][0][0][0] = dp[1][0][0][0] = 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            for (int k = 1; k <= p; k++)
            {

                if (A[i] == B[j])
                {
                    dp[i & 1][j][k][1] = ((dp[(i - 1) & 1][j - 1][k][1] + dp[(i - 1) & 1][j - 1][k - 1][0] )%mod+ dp[(i - 1) & 1][j - 1][k - 1][1])%mod;
                    dp[i & 1][j][k][0] = (dp[(i - 1) & 1][j][k][0] + dp[(i - 1) & 1][j][k][1])%mod;
                }
                else
                {
                    dp[i & 1][j][k][1] = 0;
                    dp[i & 1][j][k][0] = (dp[(i - 1) & 1][j][k][0] + dp[(i - 1) & 1][j][k][1])%mod;
                }
            }
        }
    }
    printf("%d", (dp[n & 1][m][p][1] + dp[n & 1][m][p][0])%mod);
}