#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 1000
#define INF 2e9
int maxx[MAX][MAX], minn[MAX][MAX], n, datas[2 * MAX], sum[2 * MAX];
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", datas + i);
        datas[i + n] = datas[i];
    }
    for (int i = 1; i <= 2 * n; i++)
        sum[i] = sum[i - 1] + datas[i];
    for (int step = 1; step < n; step++)
    {
        for (int i = 1, j = i + step; j < 2 * n; i++, j = i + step)
        {
            minn[i][j] = INF;
            for (int k = i; k < j; k++)
            {
                maxx[i][j] = max(maxx[i][j], maxx[i][k] + maxx[k + 1][j] + sum[j] - sum[i - 1]);
                minn[i][j] = min(minn[i][j], minn[i][k] + minn[k + 1][j] + sum[j] - sum[i - 1]);
            }
        }
    }
    int maxxx = 0, minnn = INF;
    for (int i = 1; i <= n; i++)
    {
        maxxx = max(maxxx, maxx[i][i + n - 1]);
        minnn = min(minnn, minn[i][i + n - 1]);
    }
    printf("%d\n%d", minnn, maxxx);
}