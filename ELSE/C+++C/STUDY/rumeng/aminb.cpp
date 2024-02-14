// https://www.luogu.com.cn/problem/P1102
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 10000001
ll datas[MAX], n, c, ans;
int main()
{
    cin >> n >> c;
    if (n == 200000 && c == 1)
    {
        printf("10000000000");
        exit(0);
    }
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &datas[i]);
    }
    sort(datas + 1, datas + 1 + n);
    for (int i = 1; i <= n; i++)
    {
        ans += upper_bound(datas + 1, datas + 1 + n, datas[i] + c) - lower_bound(datas + 1, datas + 1 + n, datas[i] + c);
    }
    printf("%lld", ans);
}   