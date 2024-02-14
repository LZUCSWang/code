#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 100000010
ll ans[MAX], datas[MAX];
stack<ll> s;
int n;
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", datas + i);
    }
    for (int i = n; i; i--)
    {
        while (!s.empty() && datas[i] >= datas[s.top()])
        {
            s.pop();
        }
        if (s.empty())
            ans[i] = 0;
        else
            ans[i] = s.top();
        s.push(i);
    }
    for (int i = 1; i <= n; i++)
    {
        printf("%lld ", ans[i]);
    }
}