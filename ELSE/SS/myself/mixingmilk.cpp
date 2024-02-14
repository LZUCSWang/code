#include <bits/stdc++.h>
using namespace std;
#define MAX 10001
bool cmp(pair<int, int> p1, pair<int, int> p2)
{
    return p1.first < p2.first;
}
int main()
{
    int n, m;
    cin >> n >> m;
    pair<int, int> datas[MAX];
    for (int i = 1; i <= m; i++)
    {
        cin >> datas[i].first >> datas[i].second;
    }
    sort(datas + 1, datas + m + 1, cmp);
    int cnt = 0;
    for (int i = 1; i <= m; i++)
    {
        if (n >= datas[i].second)
        {
            cnt += datas[i].first * datas[i].second;
            n -= datas[i].second;
        }
        else
        {
            cout << cnt + n * datas[i].first << endl;
            return 0;
        }
    }
    cout << cnt << endl;
    return 0;
}
