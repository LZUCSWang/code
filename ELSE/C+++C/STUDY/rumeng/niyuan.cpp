#include <bits/stdc++.h>
#define ll long long
ll n, p;
using namespace std;
#define MAX 3000001
ll datas[MAX];
int main()
{
    datas[0] = 0;
    datas[1] = 1;
    cin >> n >> p;
    printf("1\n");
    for (int i = 2; i <= n; i++)
    {
        datas[i] = (ll)(p - p / i) * datas[p % i] % p;
        printf("%lld\n", datas[i]);
    }
}