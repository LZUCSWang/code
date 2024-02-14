#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000005
typedef long long ll;
// ll a[MAXN];
ll n;
int main()
{
    ios::sync_with_stdio(false);
    cin >> n;
    int youxiu = 0, jige = 0;
    for (int i = 0; i < n; i++)
    {
        int t;
        cin >> t;
        if (t >= 85)
        {
            youxiu++;
            jige++;
        }
        else if (t >= 60)
        {
            jige++;
        }
    }
    printf("%.0f%%\n%.0f%%", double(jige) / n * 100, double(youxiu) / n * 100);
}