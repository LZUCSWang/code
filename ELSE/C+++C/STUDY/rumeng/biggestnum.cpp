#include <bits/stdc++.h>
using namespace std;
#define INF -2e9
#define MAX 1000005

int dat[MAX], m, D, nums, cnt, last;
char q;
void add(int l, int r, int k, int now)
{
    if (l == r)
    {
        dat[now] = k;
        return;
    }
    int mid = (l + r) >> 1;
    if (mid >= cnt)
        add(l, mid, k, now << 1);
    else
        add(mid + 1, r, k, now << 1 | 1);
    dat[now] = max(dat[now << 1], dat[now << 1 | 1]) % D;
}
int query(int l, int r, int ql, int qr, int now)
{
    if (ql <= l && qr >= r)
        return dat[now];
    int lval = INF, rval = INF, mid = (l + r) >> 1;
    if (mid >= ql)
        lval = max(lval, query(l, mid, ql, qr, now << 1));
    if (mid < qr)
        rval = max(rval, query(mid + 1, r, ql, qr, now << 1 | 1));
    return max(lval, rval) % D;
}
int main()
{
    cin >> m >> D;
    for (int i = 1; i <= m; i++)
    {
        scanf("\n%c %d", &q, &nums);
        if (q == 'A')
        {
            cnt++;
            add(1, m, (nums + last) % D, 1);
        }
        else
        {
            last = query(1, m, cnt - nums + 1, cnt, 1);
            printf("%d\n", last);
        }
    }
}