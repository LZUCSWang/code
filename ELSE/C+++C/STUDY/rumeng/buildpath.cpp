#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 10000001
int cha[MAX];
int n, now;
void add(int x, int k)
{
    for (; x <= n; x += x & -x)
    {
        cha[x] += k;
    }
}
ll query(int x)
{
    int ans = 0;
    for (; x; x -= x & -x)
    {
        ans += cha[x];
    }
    return ans;
}
void input()
{
    cin >> n;
    cin >> now;
    add(1, now);
    for (int i = 2; i <= n; i++)
    {
        int t;
        scanf("%d", &t);
        add(i, t - now);
        now = t;
    }
}
ll ans;
void work()
{
    int s = 1;
    while (true)
    {
        for (; s <= n && query(s) == 0; s++)
        {
        }
        if (s == n + 1)
        {
            printf("%lld", ans);
            exit(0);
        }
        int min_temp = 100000;
        int j = s;
        for (; j <= n; j++)
        {
            int temp = query(j);
            if (temp == 0)
            {
                break;
            }
            min_temp = min(min_temp, temp);
        }
        add(s, -min_temp);
        add(j, min_temp);
        ans += min_temp;
    }
}

int main()
{
    input();
    work();
}