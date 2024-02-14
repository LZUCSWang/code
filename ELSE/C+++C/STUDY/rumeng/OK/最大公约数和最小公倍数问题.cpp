#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 10000000

int n, m;
int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a % b);
}
int ans, flag;
int main()
{
    cin >> n >> m;
    long long l = 1ll * n * m;
    for (int i = 1; i <= sqrt(l); i++)
    {
        if (l % i == 0 && gcd(i, l / i) == n)
        {
            ans++;
            if (1ll * i * i == l)
                flag = 1;
        }
    }
    cout << ans * 2 - flag << endl;
}