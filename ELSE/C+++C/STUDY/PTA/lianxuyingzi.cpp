#include <bits/stdc++.h>
using namespace std;
#define MAXN 100000
// ll a[MAXN];
typedef long long ll;
ll n, res;
ll ans = 0;
ll tempans = 0;
ll last = 1;
int main()
{
    scanf("%lld", &n);
    // res = n;
    // for (ll i = 2; i < res; i++)
    // {
    //     if (n % i == 0)
    //     {
    //         res = n / i;
    //         if (last == i - 1)
    //         {
    //             tempans++;
    //             ans = max(tempans, ans);
    //         }
    //         else
    //         {
    //             tempans = 0;
    //         }
    //         last = i;
    //     }
    // }
    // printf("%d", ans);
    ll len = 0, start = 0, mulOfY;
    for (ll i = 2; i <= sqrt(n); i++)
    {
        mulOfY = 1;
        for (ll j = i; j * mulOfY <= n; j++)
        {
            mulOfY *= j;
            if (n % mulOfY == 0 && j - i + 1 > len)
            {
                len = j - i + 1;
                start = i;
            }
        }
    }
    if (start == 0)
    {
        start = n;
        len = 1;
    }
    printf("%lld\n", len);
    for (ll i = 0; i < len; i++)
    {
        printf("%lld%c", start + i, i == len - 1 ? '\n' : '*');
    }
}