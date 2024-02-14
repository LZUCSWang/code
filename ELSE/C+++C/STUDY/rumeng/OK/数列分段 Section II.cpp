// https://www.luogu.com.cn/problem/P1182
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 1000000001
int n, m, datas[100005], min_datas = 0;
void input()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", datas + i);
        min_datas = max(min_datas, datas[i]);
    }
}
bool judge(int x)
{

    int temp = 0;
    int cnt = 1;
    for (int i = 1; i <= n; i++)
    {
        if (temp + datas[i] <= x)
        {
            temp += datas[i];
        }
        else
        {
            temp = datas[i];
            cnt++;
            if (cnt > m)
            {
                return false;
            }
        }
    }
    return true;
}
int main()
{
    input();
    int l = min_datas, r = MAX;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (judge(mid))
        {
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }
    printf("%d", l);
}