#include <bits/stdc++.h>
using namespace std;
#define MAX 1000001
#define ll long long
ll tree[MAX], lazy[MAX], datas[MAX];
ll add_left, add_right, num, q_left, q_right;
ll n, m;
void push_down(ll pos, ll left, ll right)
{
    ll mid = (left + right) >> 1;
    tree[pos << 1] += lazy[pos] * (mid - left + 1);
    lazy[pos << 1] += lazy[pos];

    tree[pos << 1 | 1] += lazy[pos] * (right - mid);
    lazy[pos << 1 | 1] += lazy[pos];

    lazy[pos] = 0;
}
void build(ll pos, ll left, ll right)
{
    if (left == right)
    {
        tree[pos] = datas[left];
        return;
    }
    ll mid = (left + right) >> 1;
    build(pos << 1, left, mid);
    build(pos << 1 | 1, mid + 1, right);
    tree[pos] = tree[pos << 1] + tree[pos << 1 | 1];
}
void add(ll pos, ll now_left, ll now_right)
{
    if (now_left >= add_left && now_right <= add_right)
    {
        lazy[pos] += num;
        tree[pos] += num * (now_right - now_left + 1);
        return;
    }
    ll mid = (now_left + now_right) >> 1;
    push_down(pos, now_left, now_right);
    if (add_left <= mid)
        add(pos << 1, now_left, mid);
    if (add_right > mid)
        add(pos << 1 | 1, mid + 1, now_right);
    tree[pos] = tree[pos << 1] + tree[pos << 1 | 1];
}
ll query(ll pos, ll now_left, ll now_right)
{
    ll ans = 0;
    if (now_left >= q_left && now_right <= q_right)
        return tree[pos];
    ll mid = (now_left + now_right) >> 1;
    push_down(pos, now_left, now_right);
    if (q_left <= mid)
        ans += query(pos << 1, now_left, mid);
    if (q_right > mid)
        ans += query(pos << 1 | 1, mid + 1, now_right);
    return ans;
}
void input()
{
    cin >> n >> m;
    for (ll i = 1; i <= n; i++)
    {
        scanf("%lld", &datas[i]);
    }
}
void main_work()
{
    build(1, 1, n);
    for (ll i = 0; i < m; i++)
    {
        ll a;
        scanf("%lld", &a);
        if (a == 1)
        {
            scanf("%lld%lld%lld", &add_left, &add_right, &num);
            add(1, 1, n);
        }
        else
        {
            scanf("%lld%lld", &q_left, &q_right);
            printf("%lld\n", query(1, 1, n));
        }
    }
}
int main()
{
    input();
    main_work();
}