#include <bits/stdc++.h>
using namespace std;
long long int limit, all, dis[100000], cnt;
bool judge(long long int cnt)
{
    long long int cnt = 0, i = 1, now = 0;
    while (i < all + 1)
    {
        if (dis[i] - dis[now] < cnt)
            cnt++;
        else
            now = i;
        i++;
    }
    if (cnt <= limit)
        return true;
    return false;
}
int main()
{
    long long int m;
    cin >> m >> all >> limit;
    long long int r = m, l = 1, mid;
    dis[0] = 0;
    dis[all + 1] = m;
    for (long long int i = 1; i < all + 1; i++)
        cin >> dis[i];
    while (l <= r)
    {
        mid = (r + l) / 2;
        if (judge(mid))
        {
            cnt = mid;
            l = mid + 1;
        }
        else
        {
            r = mid - 1;
        }
        // mid = (r + l) / 2;
    }
    cout << cnt << endl;
}