#include <bits/stdc++.h>
using namespace std;
#define MAXN 1005
typedef long long ll;
ll a1, a2, d, ans;
ll n;

int main()
{
    ios::sync_with_stdio(false);
    cin >> a1 >> a2 >> n;
    d = a2 - a1;
    ans = n * a1 + (n - 1) * n / 2 * d;
    cout << ans << endl;
}