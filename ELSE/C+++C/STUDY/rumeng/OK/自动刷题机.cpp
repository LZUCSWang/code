#include <bits/stdc++.h>
// https://www.luogu.com.cn/problem/P4343
using namespace std;
#define ll long long
#define MAX 100005
// 2
// 5
// -3
// 9
ll l, k, logg, cnt, datas[MAX], min_ = -1, max_ = -1;
void input()
{
    cin >> l >> k;
    for (ll i = 1; i <= l; i++)
        scanf("%lld", datas + i);
}
void judge(ll n)
{
    cnt = logg = 0;
    for (ll i = 1; i <= l; i++)
    {
        logg += datas[i];
        if (logg < 0)
            logg = 0;
        if (logg >= n)
        {
            logg = 0;
            cnt++;
        }
    }
}
int main()
{
    input();
    ll right, left;
    right = 1e18, left = 1;
    while (left <= right)
    {
        ll mid = (left + right) >> 1;
        judge(mid);
        if (cnt >= k)
        {
            if (cnt == k)
                max_ = mid;
            left = mid + 1;
        }
        else
            right = mid - 1;
    }
    right = 1e18, left = 1;
    while (left <= right)
    {
        ll mid = (left + right) >> 1;
        judge(mid);
        if (cnt <= k)
        {
            if (cnt == k)
                min_ = mid;
            right = mid - 1;
        }
        else
            left = mid + 1;
    }
    if (min_ == -1)
        printf("-1");
    else
        printf("%lld %lld", min_, max_);
}