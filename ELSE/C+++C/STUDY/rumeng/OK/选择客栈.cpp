#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 200005
// https://www.luogu.com.cn/problem/P1311
// 5 2 3
// 0 5
// 1 3
// 0 2
// 1 4
// 1 5

int n, k, p;
int ans, pre;
int color[MAX], nums[MAX];
int main()
{
    cin >> n >> k >> p;
    for (int i = 1, pric; i <= n; i++)
    {
        scanf("%d%d", color + i, &pric);
        if (pric <= p)
        {
            for (int j = i; j > pre; j--)
                nums[color[j]]++;
            pre = i;
            ans += nums[color[i]] - 1;
        }
        else
            ans += nums[color[i]];
    }
    printf("%d", ans);
}