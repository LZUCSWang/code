// 4 3
// 2 5 4 3
// 2 1 3
// 3 2 4
// 4 2 4
// https://www.luogu.com.cn/problem/P1083
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 10000050
ll dif[MAX], l[MAX], r[MAX], d[MAX], a[MAX], n, m;
bool check(int x)
{
    memset(dif, 0, sizeof(dif));
    for (int i = 1; i <= x; i++)
    {
        dif[l[i]] += d[i];
        dif[r[i] + 1] -= d[i];  
    }
    ll need = 0;
    for (int i = 1; i <= n; i++)
    {
        need += dif[i];
        if (need > a[i])
        {
            return false;
        }
    }
    return true;
}
void input()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", a + i);
    }
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", d + i, l + i, r + i);
    }
}
int main()
{
    input();
    if (check(m))
    {
        printf("0");
        return 0;
    }
    int left = 1, right = m;
    while (left <= right)
    {
        int mid = (left + right) >> 1;
        if (check(mid))
            left = mid + 1;
        else
            right = mid - 1;
    }
    printf("-1\n%d", left);
}