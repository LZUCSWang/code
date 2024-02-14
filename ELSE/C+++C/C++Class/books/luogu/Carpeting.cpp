#include <bits/stdc++.h>
using namespace std;
#define MAX 10005
int zx[MAX], zy[MAX], yx[MAX], yy[MAX];
int main()
{
    int n, i;
    cin >> n;
    for (i = 1; i <= n; i++)
    {
        cin >> zx[i] >> zy[i] >> yx[i] >> yy[i];
    }
    int x, y;
    cin >> x >> y;
    for (i = n; i >= 1; i--)
    {
        if (zx[i] <= x && zy[i] <= y && yx[i]+zx[i] >= x && yy[i]+zy[i] >= y)
        {
            cout << i << endl;
            return 0;
        }
    }
    cout << -1 << endl;
    return 0;
}