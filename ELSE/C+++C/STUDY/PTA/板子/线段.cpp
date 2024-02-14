#include <bits/stdc++.h>
using namespace std;
#define MAX 100005
int tree[MAX], datas[MAX], lazy[MAX];
int n;
int num, al, ar, ql, qr;
void build(int pos, int l, int r)
{
    if (l == r)
    {
        tree[pos] = datas[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(pos << 1, l, mid);
    build(pos << 1 | 1, mid + 1, r);
    tree[pos] = tree[pos << 1] + tree[pos << 1 | 1];
}
void push_down(int pos, int l, int r)
{
    int mid = (l + r) >> 1;
    tree[pos << 1] += lazy[pos] * (mid - l + 1);
    lazy[pos << 1] += lazy[pos];

    tree[pos << 1 | 1] += lazy[pos] * (r - mid);
    lazy[pos << 1 | 1] += lazy[pos];

    lazy[pos] = 0;
}
void add(int pos, int l, int r)
{
    if (l >= al && r <= ar)
    {
        tree[pos] += num * (l - r + 1);
        lazy[pos] += num;
        return;
    }
    int mid = (l + r) >> 1;
    push_down(pos, l, r);
    if (al <= mid)
        add(pos << 1, l, mid);
    if (ar > mid)
        add(pos << 1 | 1, mid + 1, r);
    tree[pos] = tree[pos << 1] + tree[pos << 1 | 1];
}

int query(int pos, int l, int r)
{
    int ans = 0;
    if (l >= ql && r <= qr)
    {
        ans = tree[pos];
        return ans;
    }
    int mid = (l + r) >> 1;
    push_down(pos, l, r);
    if (l <= mid)
        ans += query(pos << 1, l, mid);
    if (r > mid)
        ans += query(pos << 1 | 1, mid + 1, r);
    return ans;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", datas + i);
    build(1, 1, n);
    for (int i = 1; i <= 10; i++)
    {
        printf("%d ", tree[i]);
    }
}