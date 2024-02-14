#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000005
int n, a[MAXN], t[MAXN];
long long ans;
void msort(int l, int r)
{
    if (l == r)
        return;
    int mid = (l + r) >> 1, lp = l, rp = mid + 1, tp = lp;
    msort(l, mid);
    msort(mid + 1, r);
    while (lp <= mid && rp <= r)
    {
        if (a[lp] <= a[rp])
        {
            t[tp++] = a[lp++];
        }
        else
        {
            t[tp++] = a[rp++];
            ans += mid - lp + 1;
        }
    }
    while (lp <= mid)
    {
        t[tp++] = a[lp++];
    }
    while (rp <= r)
    {
        t[tp++] = a[rp++];
    }
    for (int i = l; i <= r; i++)
    {
        a[i] = t[i];
    }
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", a + i);
    }
    msort(1, n);
    // for (int i = 1; i <= n; i++)
    // {
    //     cout << a[i] << ' ';
    // }
    cout << ans << endl;
}