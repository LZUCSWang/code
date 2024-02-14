#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
int R[maxn];
map<int, int> last;
int n, m, x;
int main()
{
    ios::sync_with_stdio(false);
    cin >> n >> m >> x;
    for (int i = 1; i <= n; i++)
    {
        int a;
        cin >> a;
        R[i] = max(R[i - 1], last[a ^ x]);
        // printf("R[%d] = %d", i, R[i]);
        last[a] = i;
    }

    while (m--)
    {
        int l, r;
        cin >> l >> r;
        if (R[r] >= l)
            cout << "yes" << endl;
        else
            cout << "no" << endl;
    }
}