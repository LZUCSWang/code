#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 10000000
#define ll long long

ll n, m, k, x;
ll quick_pow(ll a, ll b)
{
    ll ans = 1;
    while (b)
    {
        if (b & 1)
            ans = ans * a % n;
        a = a * a % n;
        b >>= 1;
    }
    return ans;
}
int main()
{
    scanf("%lld%lld%lld%lld", &n, &m, &k, &x);
    printf("%lld", (m*quick_pow(10,k)%n+x) % n);
}