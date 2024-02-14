#include <bits/stdc++.h>
using namespace std;
#define MAX 1000005
#define ll long long
int chaFen[MAX], n;
void add(int i, int x)
{
    while (i <= n)
    {
        chaFen[i] += x;
        i += i & -i;
    }
}
int query(int i)
{
    int ans = 0;
    while (i)
    {
        ans += chaFen[i];
        i -= i & -i;
    }
    return ans;
}
void input()
{
    cin >> n;
    int nowNum;
    cin >> nowNum;
    add(1, nowNum);
    for (int i = 2; i <= n; i++)
    {
        int num;
        cin >> num;
        add(i, num - nowNum);
        nowNum = num;
    }
}
ll ans;
void work()
{
    int start = 1;
    while (true)
    {
        for (; start <= n && query(start) == 0; start++)
        {
        }
        if (start > n)
        {
            cout << ans << endl;
            exit(0);
        }
        int end = start, min_ = 0x3f3f3f3f;
        for (; end <= n; end++)
        {
            int nowQ = query(end);
            if (nowQ == 0)
            {
                break;
            }
            min_ = min(min_, nowQ);
        }
        add(start, -min_);
        add(end, min_);
        ans += min_;
    }
}
int main()
{
    input();
    work();
}