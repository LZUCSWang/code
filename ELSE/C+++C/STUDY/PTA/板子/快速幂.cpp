#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main()
{
    int a, b, c;
    int ans = 1;
    scanf("%d%d%d", &a, &b, &c);
    int bb = b;
    while (b)
    {
        if (b & 1)
            ans = ans * a % c;
        a = a * a % c;
        b >>= 1;
    }
    ans %= c;
    printf("%d^%d mod %d=%d", a, bb, c, ans);
    return 0;
}