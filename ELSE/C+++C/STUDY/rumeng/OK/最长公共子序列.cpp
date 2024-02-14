#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 1000000
// https://www.luogu.com.cn/problem/P1439
int n;
int mapp[MAX], ans[MAX];
int main()
{
    cin >> n;
    for (int i = 1, t; i <= n; i++)
    {
        scanf("%d", &t);
        mapp[t] = i;
    }
    memset(ans, 0x3f3f3f, sizeof(ans));
    for (int i = 1, t; i <= n; i++)
    {
        scanf("%d", &t);
        t = mapp[t];
        *lower_bound(ans + 1, ans + n + 1, t) = t;
    }
    printf("%d", lower_bound(ans + 1, ans + n + 1, ans[0]) - ans - 1);
}