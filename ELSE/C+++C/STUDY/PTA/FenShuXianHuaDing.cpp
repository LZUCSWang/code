#include <bits/stdc++.h>
using namespace std;
#define MAXN 10050
typedef long long ll;
// ll a[MAXN];
int n, m;
typedef pair<int, int> p;
p P[MAXN];
int main()
{
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> P[i].first >> P[i].second;
    }
    sort(P + 1, P + n + 1, [&](p a, p b)
         { return (a.second > b.second) || (a.second == b.second && a.first < b.first); });
    int M = m * 1.5;
    if (n <= M)
    {
        cout << P[n].second << ' ' << n << endl;
        for (int i = 1; i <= n; i++)
        {
            cout << P[i].first << ' ' << P[i].second << endl;
        }
        return 0;
    }
    // cout << M << endl;
    for (int i = M; i <= n; i++)
    {
        if (P[i].second == P[i + 1].second)
            M++;
        else
            break;
    }
    cout << P[M].second << ' ' << M << endl;
    for (int i = 1; i <= M; i++)
    {
        cout << P[i].first << ' ' << P[i].second << endl;
    }
}