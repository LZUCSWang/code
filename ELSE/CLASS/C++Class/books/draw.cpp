#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
#define MAX 100000
// 抽签
int main()
{
    int data[MAX], kk[MAX] = {MAX};
    int n, m;
    cin >> n;
    cin >> m;
    for (int i = 0; i < n; i++)
    {
        cin >> data[i];
    }
    for (int c = 0; c < n; c++)
    {
        for (int d = 0; d < n; d++)
        {
            kk[c * n + d] = data[c] + data[d];
        }
    }
    sort(kk, kk + n * n);
    for (int datas = 0; datas < n; datas++)
    {
        for (int b = 0; b < n; b++)
        {
            if (binary_search(kk, kk + n * n, m - data[datas] - data[b]))
            {
                cout << "yes" << endl;
                return 0;
            }
        }
    }
    cout << "no" << endl;
}