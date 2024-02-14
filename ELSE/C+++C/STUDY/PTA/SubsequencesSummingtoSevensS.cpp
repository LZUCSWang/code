#include <bits/stdc++.h>
using namespace std;
int n, a[50005];
int lf[8], rf[8];
int ans = 0;
int main()
{
    scanf("%d", &n);
    scanf("%d", a + 1);
    a[1] %= 7;
    if (a[1] == 0)
        ans = 1;
    bool flag = false;
    for (int i = 2; i <= n; i++)
    {
        int t;
        scanf("%d", &t);
        a[i] = (a[i - 1] + t) % 7;
        if (a[i] == 0)
            ans = 1;
    }
    int cnt = 0;
    for (int i = 1; i <= n && cnt < 7; i++)
    {
        if (!lf[a[i]])
        {
            lf[a[i]] = i;
            cnt++;
        }
        if (a[i] == 0)
            ans = max(ans, i);
    }
    cnt = 0;
    // cout<<a[0]<<endl;
    for (int i = n; i >= 1 && cnt < 7; i--)
    {
        if (!rf[a[i]])
        {
            rf[a[i]] = i;
            cnt++;
        }
    }
    for (int i = 0; i <= 6; i++)
    {
        if (lf[i] && rf[i])
            ans = max(ans, rf[i] - lf[i]);
    }
    printf("%d", ans);
}