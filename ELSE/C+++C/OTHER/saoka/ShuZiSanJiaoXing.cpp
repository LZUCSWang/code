#include <bits/stdc++.h>
using namespace std;
#define MAXN 105
typedef long long ll;
ll a[MAXN][MAXN];
ll n;
int main()
{
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            cin >> a[i][j];
        }
    }
    for (int i = 2; i <= n; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            if (j == 1)
            {
                a[i][j] += a[i - 1][j];
            }
            else if (j == i)
            {
                a[i][j] += a[i - 1][j - 1];
            }
            else
            {
                a[i][j] = max(a[i - 1][j - 1], a[i - 1][j]) + a[i][j];
            }
        }
    }
    if (n % 2 == 0)
    {
        cout << max(a[n][n / 2], a[n][n / 2 + 1]);
    }
    else
    {
        cout << a[n][(n + 1) / 2];
    }
}