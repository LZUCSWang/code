// 2
// 41 1 96 288
// 95 1 37 1776
#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 10000000

int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a % b);
}
int a0, a1, b0, b1;
int t;
int a01, b10;
int main()
{
    cin >> t;
    while (t--)
    {
        int ans = 0;
        scanf("%d%d%d%d", &a0, &a1, &b0, &b1);
        a01 = a0 / a1, b10 = b1 / b0;
        for (int i = 1; i <= sqrt(b1); i++)
        {
            if (b1 % i == 0)
            {
                int j = b1 / i;
                if (i % a1 == 0 && gcd(b10, b1 / i) == 1 && gcd(a01, i / a1) == 1)
                    ans++;
                if (i == j)
                    continue;
                if (j % a1 == 0 && gcd(b10, b1 / j) == 1 && gcd(a01, j / a1) == 1)
                    ans++;
            }
        }
        printf("%d\n", ans);
    }
}