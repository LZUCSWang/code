#include <bits/stdc++.h>
using namespace std;
#define MAXN 1005
typedef long long ll;
typedef pair<ll, pair<ll, ll>> node;
map<node, ll> mp;
ll w(ll a, ll b, ll c)
{
    node tnode = make_pair(a, make_pair(b, c));
    if (mp.find(tnode) != mp.end())
    {
        return mp[tnode];
    }
    else if (a <= 0 || b <= 0 || c <= 0)
    {
        return 1;
    }
    else if (a > 20 || b > 20 || c > 20)
    {
        return mp[tnode] = w(20, 20, 20);
    }
    else if (a < b && b < c)
    {
        return mp[tnode] = w(a, b, c - 1) + w(a, b - 1, c - 1) - w(a, b - 1, c);
    }
    else
    {
        return mp[tnode] = w(a - 1, b, c) + w(a - 1, b - 1, c) + w(a - 1, b, c - 1) - w(a - 1, b - 1, c - 1);
    }
}
int main()
{
    ios::sync_with_stdio(false);
    ll a, b, c;
    while (cin >> a >> b >> c)
    {
        if (a == -1 && b == -1 && c == -1)
            break;
        cout << "w(" << a << ", " << b << ", " << c << ") = " << w(a, b, c) << endl;
    }
}