#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 10000001
ll n, k;
bool isprime(ll x)
{
    for (int i = 2; i <= sqrt(x); i++)
    {
        if (x % i == 0)
        {
            return false;
        }
    }
    return true;
}
int main()
{
    cin >> n >> k;
    if (2 * k + 2 > n + 1 && isprime(k + 1))
    {
        cout << 1 << endl;
    }
    else
        cout << 2 << endl;
}