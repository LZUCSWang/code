#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
#define MAX 100000
int main()
{
    int n, len;
    cin >> len;
    cin >> n;
    int datas[n];
    for (int i = 0; i < n; i++)
    {
        cin >> datas[i];
    }
    // for (int i = 0; i < n; i++)
    // {
    //     cout << datas[i] << " ";
    // }

    int minnum = 0, MAXum = 0;
    for (int i = 0; i < n; i++)
    {
        minnum = max(minnum, min(datas[i], len - datas[i]));
    }
    for (int i = 0; i < n; i++)
    {
        MAXum = max(MAXum, max(datas[i], len - datas[i]));
    }
    cout << minnum << endl;
    cout << MAXum << endl;
}