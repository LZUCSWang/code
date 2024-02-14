#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
#define MAX 100000
int main()
{
    int l, n;
    cin >> l >> n;
    int datas[l + 1];
    memset(datas, 0, sizeof(datas));
    int s, e;
    for (int i = 0; i < n; i++)
    {
        cin >> s >> e;
        for (int j = s; j <= e; j++)
        {
            datas[j] = 1;
        }
    }
    int cnt = 0;
    for (int i = 0; i <= l; i++)
    {
        if (datas[i] == 0)
            cnt++;
    }
    cout << cnt << endl;
}