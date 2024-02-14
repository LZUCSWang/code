#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 10000001
#define MOD 1000000007
int main()
{
    ll n, m, l;
    cin >> m;
    while (m--)
    {
        scanf("%lld%lld", &n, &l);
        if (n == 1)
        {
            printf("0\n");
            continue;
        }
        n = (ll)log2(n);
        printf("%lld\n", (((l / 2) * (l - l / 2) % MOD) * (((1ll << (n + 1)) - 1) % MOD)) % MOD);
    }
}