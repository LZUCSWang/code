// https://www.luogu.com.cn/problem/P2661
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 200005
int f[MAX];
int cnt;
int fa(int x)
{
    cnt++;
    if (f[x] == x)
        return x;
    else
        return fa(f[x]);
}
int n, t;

int main()
{
    cin >> n;
    int ans = MAX * 100;
    for (int i = 1; i <= n; i++)
        f[i] = i;
    for (int i = 1; i <= n; i++)
    {
        cnt = 0;
        scanf("%d", &t);
        if (fa(t) == i)
            ans = min(ans, cnt);
        else
            f[i] = t;
    }
    printf("%d", ans);
}