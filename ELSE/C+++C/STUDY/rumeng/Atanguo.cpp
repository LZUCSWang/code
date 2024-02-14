#include <bits/stdc++.h>
using namespace std;
#define MAX 1000001
long long n, x;
long long datas[MAX];
void input()
{
    cin >> n >> x;
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &datas[i]);
    }
}
int main()
{
    input();
    int addans = 0;
    if (datas[1] > x)
    {
        addans += datas[1] - x;
        datas[1] = x;
    }
    long long ans = 0;

    for (long long i = 2; i <= n; i++)
    {
        if (datas[i] + datas[i - 1] > x)
        {
            long long tp = datas[i] + datas[i - 1] - x;
            ans += tp;
            datas[i] = datas[i] - tp;
        }
    }
    printf("%lld", ans + addans);
}