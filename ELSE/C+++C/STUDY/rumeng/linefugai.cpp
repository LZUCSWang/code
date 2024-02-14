#include <bits/stdc++.h>
using namespace std;
#define MAX 5
struct node
{
    long long s, e;
} points[MAX];
bool cmp(node a, node b)
{
    return a.e < b.e;
}
int main()
{
    long long n;
    cin >> n;
    for (long long i = 0; i < n; i++)
    {
        scanf("%lld%lld", &points[i].s, &points[i].e);
    }
    sort(points, points + n, cmp);
    long long last_time = 0, ans = 0;
    for (long long i = 0; i < n; i++)
    {
        if (points[i].s >= last_time)
        {

            ans++;
            last_time = points[i].e;
        }
    }
    printf("%lld", ans);
}