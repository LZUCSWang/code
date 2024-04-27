#include <bits/stdc++.h>
using namespace std;
long long int n;
long long int A1, a, b, SA;
int main()
{
    cin >> n;
    cin >> A1 >> a >> b >> SA;
    long long int res = SA - A1 * n;
    long long int x = (res + (n - 1) * n / 2 * b) / (a + b);
    long long int y = (n - 1) * n / 2 - x;
    printf("%lld ", A1);
    for (long long int i = 1; i < n; i++)
    {
        if (x >= y)
        {
            A1 += a;
            x -= (n - i);
        }
        else
        {
            A1 -= b;
            y -= (n - i);
        }
        printf("%lld", A1);
        if (i != n - 1)
            printf(" ");
    }
}