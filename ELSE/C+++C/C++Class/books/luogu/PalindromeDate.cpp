#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
// #define MAX 100000
int month[13] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int main()
{
    int cnt = 0, n, m;
    cin >> n;
    cin >> m;
    for (int i = 1; i <= 12; i++)
    {
        for (int j = 1; j <= month[i]; j++)
        {
            int last = (i / 10) + (i % 10) * 10 + (j / 10) * 100 + (j % 10) * 1000;
            int s = last * 10000 + i * 100 + j;
            if (s < n || s > m)
                continue;
            cnt++;
        }
    }
    cout << cnt << endl;
}