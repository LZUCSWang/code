// 2 10
// 1
// -2
// 1
// https://www.luogu.com.cn/problem/P2312
#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 100000000
#define ll long long
const ll mod = 998244353;
ll nums[MAX];
ll n, m;
ll cnt, ans[MAX];
inline ll read()
{
    ll sum = 0;
    int flag = 1;
    char c;
    c = getchar();
    while (c < '0' or c > '9')
    {
        if (c == '-')
            flag = -1;
        c = getchar();
    }
    while (c >= '0' and c <= '9')
    {
        sum = (sum * 10 + c - '0') % mod;
        c = getchar();
    }
    return sum * flag;
}
bool judge(ll now)
{

    ll sum = 0;
    for (ll i = n; i; i--)
    {
        sum = ((nums[i] + sum) * now) % mod;
    }
    sum = (sum + nums[0]) % mod;
    return sum == 0;
}

int main()
{
    cin >> n >> m;
    for (ll i = 0, t; i <= n; i++)
    {
        nums[i] = read();
    }
    for (ll i = 1; i <= m; i++)
    {
        if (judge(i))
        {
            ans[++cnt] = i;
        }
    }
    cout << cnt << endl;
    for (ll i = 1; i <= cnt; i++)
    {
        printf("%lld\n", ans[i]);
    }
}