#include <bits/stdc++.h>
using namespace std;
int main()
{
    long long int a, b, p;
    cin >> a >> b >> p;
    long long int aa = a, bb = b, pp = p;
    long long int ans = 1;
    while (b)
    {
        if (b & 1)
        {
            ans *= a;
            ans %= p;
        }
        a *= a;
        a %= p;
        b >>= 1;
    }
    printf("%lld^%lld mod %lld=%lld", aa, bb, pp, ans % p);
}