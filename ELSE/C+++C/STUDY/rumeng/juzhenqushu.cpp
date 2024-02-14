#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 100
long long p = 1e18;
struct int128
{
    long long hig;
    long long low;
} a[MAX][MAX], f[MAX][MAX], ans;
int128 max(int128 a, int128 b)
{
    if (a.hig > b.hig)
        return a;
    if (a.hig < b.hig)
        return b;
    if (a.low > b.low)
        return a;
    if (a.low < b.low)
        return b;
    return a;
}
int128 operator+(int128 a, int128 b)
{
    int128 k;
    k.low = k.hig = 0;
    k.low = a.low + b.low;
    k.hig = k.low / p + a.hig + b.hig;
    k.low %= p;
    return k;
}
int128 operator*(int128 a, int b)
{
    int128 k;
    k.low = k.hig = 0;
    k.low = a.low * b;
    k.hig += k.low / p + b * a.hig;
    k.low %= p;
    return k;
}

int n, m;
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%lld", &a[i][j].low);
    for (int i = 1; i <= n; i++)
    {
        for (int len = 1; len <= m; len++)
            for (int left = 1, right = left + len - 1; right <= m; left++, right++)
                f[left][right] = max(f[left + 1][right] + a[i][left], f[left][right - 1] + a[i][right]) * 2;
        ans = ans + f[1][m];
    }
    if (ans.hig)
        printf("%lld%018lld", ans.hig, ans.low);
    else
        printf("%lld", ans.low);
}