#include <bits/stdc++.h>
using namespace std;
#define MAXN 100000
typedef pair<double, double> PDD;
typedef pair<int, int> PII;
set<PII> s;
// int a[MAXN];
int n;
double x, y;
int main()
{
    cin >> n;
    int ans = 1;
    for (int i = 0; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        if (s.find({a, b}) != s.end())
            continue;
        s.insert({a, b});
        ans++;
        set<PDD> jd;
        for (auto it = s.begin(); it != s.end(); it++)
        {
            x = 1.0 * (b - it->second) / (it->first - a);
            y = a * x + b;
            if (a != it->first && (jd.find({x, y}) == jd.end() || jd.empty())) // 第一个条件是不平行，第二个条件是交点不重复
            {
                ans++;
                jd.insert({x, y});
            }
        }
    }
    cout << ans;
}