#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MAXN 1000005
ll q[MAXN];
int n, x;
bool check(int mid)
{
    for (int i = 1; i < n - mid + 1; i++)
    {
        if (q[i + mid - 1] - q[i - 1] < 2 * x)
            return false;
    }
    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> n >> x;
    for (int i = 1; i < n; i++)
    {
        int a;
        cin >> a;
        q[i] = q[i - 1] + a;
    }
    int l = 1, r = n;
    while (l != r)
    {
        int mid = (r + l) / 2;
        if (check(mid))
            r = mid;
        else
            l = mid + 1;
    }
    cout << l << endl;
}