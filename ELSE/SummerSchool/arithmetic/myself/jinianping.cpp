#include <bits/stdc++.h>
using namespace std;
#define MAX 100001
int datas[MAX];
bool cmp(int datas, int b)
{
    return datas > b;
}
int main()
{
    int n, m;
    cin >> n;
    cin >> m;
    for (int i = 1; i <= m; i++)
    {
        cin >> datas[i];
    }
    sort(datas + 1, datas + m + 1, cmp);
    int left = 1, right = m, cnt = 0;
    while (left < right)
    {
        if (datas[left] + datas[right] <= n)
            right--;
        left++;
        cnt++;
    }
    if (right < left)
        cout << cnt;
    else
        cout << cnt + 1;
}