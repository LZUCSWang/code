#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 10000001
// https://www.luogu.com.cn/problem/P2024
// 100 7
// 1 101 1
// 2 1 2
// 2 2 3
// 2 3 3
// 1 1 3
// 2 3 1
// 1 5 5
int n, k, ans, parent[MAX];
int fa(int x)
{
    return (x == parent[x]) ? x : parent[x] = fa(parent[x]);
}
void unity(int a, int b)
{
    int fx = fa(a), fy = fa(b);
    parent[fx] = fy;
}
int main()
{
    cin >> n >> k;
    for (int i = 1; i <= 3 * n; i++)
    {
        parent[i] = i;
    }
    while (k--)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        if (b > n || c > n)
        {
            ans++;
            continue;
        }
        if (a == 1)
        {
            if (fa(b + n) == fa(c) || fa(b + 2 * n) == fa(c))
            {
                ans++;
                continue;
            }
            unity(b, c), unity(b + n, c + n), unity(b + 2 * n, c + 2 * n);
        }
        else
        {
            if (b == c)
            {
                ans++;
                continue;
            }
            if (fa(b) == fa(c) || fa(b + 2 * n) == fa(c))
            {
                ans++;
                continue;
            }
            unity(b, c + 2 * n), unity(b + n, c), unity(b + 2 * n, c + n);
        }
    }
    printf("%d", ans);
}