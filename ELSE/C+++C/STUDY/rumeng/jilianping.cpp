// 6 1 100
// 50
// 20
// 25
// 20
// 25
// 50

#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 10000
#define ll long long

int t, n, m, price[MAX][MAX], f[MAX];
void input()
{
    scanf("%d%d%d", &t, &n, &m);
    for (int i = 1; i <= t; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            scanf("%d", &price[i][j]);
        }
    }
}
int main()
{
    input();
    for (int day = 1; day < t; day++)
    {
        memset(f, 0, sizeof(f));
        for (int item = 1; item <= n; item++)
        {
            for (int remon = price[day][item]; remon <= m; remon++)
            {
                f[remon] = max(f[remon], f[remon - price[day][item]] + price[day + 1][item] - price[day][item]);
            }
        }
        m += f[m];
    }
    printf("%d", m);
}