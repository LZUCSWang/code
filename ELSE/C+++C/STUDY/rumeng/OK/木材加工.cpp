// https://www.luogu.com.cn/problem/P2440
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 1000000001
// 3 7
// 232
// 124
// 456
int n, k;
int datas[100005];
unsigned long long datas_sum;
void input()
{
    for (ll i = 1; i <= n; i++)
    {
        scanf("%d", datas + i);
        datas_sum += datas[i];
    }
}
bool judge(ll x)
{
    unsigned long long sum = 0;
    for (ll i = 1; i <= n; i++)
    {
        sum += datas[i] / x;
        if (sum >= k)
        {
            return true;
        }
    }
    if (sum >= k)
    {
        return true;
    }
    return false;
}
int main()
{
    cin >> n >> k;
    input();
    if (datas_sum < k)
    {
        printf("0");
        return 0;
    }
    ll l = 1, r = MAX;
    while (l <= r)
    {
        ll mid = (l + r) >> 1;
        if (judge(mid))
        {
            l = mid + 1;
        }
        else
        {
            r = mid - 1;
        }
    }
    cout << r;
}