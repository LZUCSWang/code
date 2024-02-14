#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 10000001
ll Max[MAX][21];
ll lefts, rights;
ll n, m;
void input()
{
    cin >> n >> m;
    for (ll i = 1; i <= n; i++)
    {
        scanf("%lld", &Max[i][0]);
    }
}
void build()
{
    for (ll j = 1; j <= 21; j++)
    {
        for (ll i = 1; i + (1 << j) - 1 <= n; i++)
        {
            Max[i][j] = max(Max[i][j - 1], Max[i + (1 << (j - 1))][j - 1]);
        }
    }
}
long long query()
{
    ll lenths = log2(rights - lefts + 1);
    return max(Max[lefts][lenths], Max[rights - (1 << lenths) + 1][lenths]);
}
void main_work()
{
    while (m--)
    {
        scanf("%lld%lld", &lefts, &rights);
        printf("%lld\n", query());
    }
}
int main()
{
    input();
    build();
    main_work();
}