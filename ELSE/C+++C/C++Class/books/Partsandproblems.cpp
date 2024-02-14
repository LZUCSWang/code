#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
#define MAX 100000
int n, m;
int datas[MAX];
bool dfs(int i, int sum)
{
    if (i == n)
        return sum == m;
    if (sum > m)
        return false;
    if (dfs(i + 1, sum))
        return true;
    if (dfs(i + 1, sum + datas[i]))
        return true;
    return false;
}
int main()
// 判断一个数组中选若干个数是否可行
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        cin >> datas[i];
    }
    if (dfs(0, 0))
    {
        cout << "yes" << endl;
    }
    else
    {
        cout << "no" << endl;
    }
}