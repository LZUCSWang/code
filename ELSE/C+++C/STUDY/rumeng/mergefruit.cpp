#include <bits/stdc++.h>
using namespace std;
priority_queue<int, vector<int>, greater<int>> q;
int main()
{
    int n, ans;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        int t;
        scanf("%d", &t);
        q.push(t);
    }
    while (q.size() >= 2)
    {
        int a = q.top();
        q.pop();
        int b = q.top();
        q.pop();
        ans += a + b;
        q.push(a + b);
    }
    printf("%d", ans);
}