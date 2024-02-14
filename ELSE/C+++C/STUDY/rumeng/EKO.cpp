#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 10000001
int n, m;
int datas[MAX];
bool judge(int ans)
{
    int sum = 0;
    for (int i = 1; i <= n; i++)
    {
        if (datas[i] > ans)
        {
            sum += datas[i] - ans;
            if (sum >= m)
            {
                return true;
            }
        }
    }
    return false;
}
int main()
{
    cin >> n >> m;
    int right = 0;
    int left = 0;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &datas[i]);
        right = max(datas[i], right);
    }
    while (left <= right)
    {
        int mid = (right + left) >> 1;
        if (judge(mid))
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    printf("%d",right);
}