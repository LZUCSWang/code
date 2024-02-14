#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
#define MAX 101
int flag[20000]={0};
int main()
{
    int n, datas[MAX];
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> datas[i];
    }
    sort(datas, datas + n);
    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (binary_search(datas, datas + n, datas[i] + datas[j]))
            {
                if (flag[datas[i] + datas[j]] == 0)
                    cnt++;
                flag[datas[i] + datas[j]] = 1;
            }
        }
    }
    cout << cnt << endl;
}