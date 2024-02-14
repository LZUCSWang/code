#include <bits/stdc++.h>
using namespace std;
// #define MAXN 1005
// typedef long long ll;
// ll a[MAXN];
int n;
set<int> s;
int main()
{
    ios::sync_with_stdio(false);
    cin >> n;
    int x;
    while (n--)
    {
        cin >> x;
        s.insert(x);
    }
    cout << s.size() << endl;
    while (!s.empty())
    {
        cout << *s.begin() << ' ';
        s.erase(s.begin());
    }
}