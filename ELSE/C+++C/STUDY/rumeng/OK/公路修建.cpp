// https://www.luogu.com.cn/problem/P1265
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 5005
double dis[MAX], min_, newdis, ans;
int n, x[MAX], y[MAX], pos;
bool vis[MAX];
inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
inline void prime()
{
    dis[1] = 0;
    for (int i = 1; i <= n; i++)
    {
        pos = 1;
        min_ = 10e9;
        for (int j = 1; j <= n; j++)
        {
            if (!vis[j] && dis[j] < min_)
            {
                min_ = dis[j];
                pos = j;
            }
        }
        vis[pos] = true;
        ans += min_;
        if (i == n)
            break;
        for (int j = 1; j <= n; j++)
        {
            if (vis[j])
                continue;
            newdis = sqrt(pow(x[pos] - x[j], 2) + pow(y[pos] - y[j], 2));
            if (newdis < dis[j])
                dis[j] = newdis;
        }
    }
    printf("%.2lf", ans);
}
inline void input()
{
    n = read();
    for (int i = 1; i <= n; i++)
    {
        x[i] = read();
        y[i] = read();
        dis[i] = 10e9;
    }
}
int main()
{
    input();
    prime();
}