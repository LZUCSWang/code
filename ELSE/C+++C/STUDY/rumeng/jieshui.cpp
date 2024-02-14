#include <bits/stdc++.h>
using namespace std;
#define MAX 10000001
pair<long long, long long> datas[MAX];
bool cmp(pair<long long, long long> a, pair<long long, long long> b)
{
    return a.first < b.first;
}
int main()
{
    long long n;
    cin >> n;
    long long ans = 0, allans = 0;
    for (long long i = 1; i <= n; i++)
    {
        scanf("%lld", &datas[i].first);
        datas[i].second = i;
    }
    sort(datas + 1, datas + 1 + n, cmp);
    for (long long i = 1; i < n; i++)
    {
        printf("%lld ", datas[i].second);
        ans += datas[i].first;
        allans += ans;
    }
    printf("%lld\n", datas[n].second);
    printf("%.2lf", allans * 1.0 / (n));
}