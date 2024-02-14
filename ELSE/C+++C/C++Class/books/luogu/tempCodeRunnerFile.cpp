#include <bits/stdc++.h>
using namespace std;
int all, limit, n;
int judge(int cnt, int data[])
{
    int i = 1, now = 0, cnt = 0;
    while (i <= n)
    {
        if (data[i] - data[now] <= cnt)
            cnt++;
        else
            now = i;
        i++;
    }
    if (limit >= cnt)
        return 1;
    return 0;
}
int main()
{
    cin >> all >> n >> limit;
    int data[100];
    data[0] = 0;
    data[n + 1] = all;
    for (int i = 1; i <= n; i++)
        cin >> data[i];
    int l = 1, r = all, mid;
    while (l <= r)
    {
        mid = (l + r) / 2;
        if (judge(mid, data) == 1)
            l = mid + 1;
        else
            r = mid - 1;
    }
    cout << l;
}