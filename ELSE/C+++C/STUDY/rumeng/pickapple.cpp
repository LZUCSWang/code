#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 10000001
ll n, s, a, b;
#define node pair<int, int>
node apple[MAX];
bool cmp(node a, node b)
{
    return a.second < b.second;
}
void input()
{
    cin >> n >> s;
    cin >> a >> b;
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld%lld", &apple[i].first, &apple[i].second);
    }
    sort(apple + 1, apple + 1 + n, cmp);
}
ll cnt;
int main()
{
    input();
    for (ll i = 1; i <= n && s > 0; i++)
    {
        if (a + b >= apple[i].first&&s>=apple[i].second)
        {
            s -= apple[i].second;
            cnt++;
        }
    }
    cout << cnt;
}