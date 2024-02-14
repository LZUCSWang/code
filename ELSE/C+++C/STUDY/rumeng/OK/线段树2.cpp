// https://www.luogu.com.cn/problem/P3373
#include <bits/stdc++.h>
using namespace std;
#define MAX 10000001
#define ll long long
ll tree[MAX], lazy_add[MAX], datas[MAX], lazy_mul[MAX];
ll add_left, add_right, num, q_left, q_right;
ll n, m, mod;
void push_down(ll pos, ll left, ll right)
{
    ll mid = (left + right) >> 1;
    tree[pos << 1] = ((lazy_add[pos] * (mid - left + 1)) % mod + lazy_mul[pos] * tree[pos << 1]) % mod; //修改左右子树
    tree[pos << 1 | 1] = ((lazy_add[pos] * (right - mid)) % mod + lazy_mul[pos] * tree[pos << 1 | 1]) % mod;

    lazy_mul[pos << 1] = (lazy_mul[pos << 1] * lazy_mul[pos]) % mod; //修改左右子树mul值
    lazy_mul[pos << 1 | 1] = (lazy_mul[pos << 1 | 1] * lazy_mul[pos]) % mod;

    lazy_add[pos << 1] = (lazy_add[pos] + lazy_add[pos << 1] * lazy_mul[pos]) % mod; //修改左右子树add值，此时需要×上根的mul值
    lazy_add[pos << 1 | 1] = (lazy_add[pos] + lazy_add[pos << 1 | 1] * lazy_mul[pos]) % mod;

    lazy_add[pos] = 0, lazy_mul[pos] = 1;
}
void build(ll pos, ll left, ll right)
{
    lazy_mul[pos] = 1;
    if (left == right)
    {
        tree[pos] = datas[left] % mod;
        return;
    }
    ll mid = (left + right) >> 1;
    build(pos << 1, left, mid);
    build(pos << 1 | 1, mid + 1, right);
    tree[pos] = (tree[pos << 1] + tree[pos << 1 | 1]) % mod;
}
void add(ll pos, ll now_left, ll now_right)
{
    if (now_left >= add_left && now_right <= add_right)
    {
        lazy_add[pos] = (lazy_add[pos] + num) % mod;
        tree[pos] = (tree[pos] + num * (now_right - now_left + 1)) % mod;
        return;
    }
    ll mid = (now_left + now_right) >> 1;
    push_down(pos, now_left, now_right);
    if (add_left <= mid)
        add(pos << 1, now_left, mid);
    if (add_right > mid)
        add(pos << 1 | 1, mid + 1, now_right);
    tree[pos] = (tree[pos << 1] + tree[pos << 1 | 1]) % mod;
}
void mul(ll pos, ll now_left, ll now_right)
{
    if (now_left >= add_left && now_right <= add_right)
    {
        lazy_add[pos] = (lazy_add[pos] * num) % mod;
        lazy_mul[pos] = (lazy_mul[pos] * num) % mod;
        tree[pos] = (tree[pos] * num) % mod;
        return;
    }
    ll mid = (now_left + now_right) >> 1;
    push_down(pos, now_left, now_right);
    if (add_left <= mid)
        mul(pos << 1, now_left, mid);
    if (add_right > mid)
        mul(pos << 1 | 1, mid + 1, now_right);
    tree[pos] = (tree[pos << 1] + tree[pos << 1 | 1]) % mod;
}
ll query(ll pos, ll now_left, ll now_right)
{
    ll ans = 0;
    if (now_left >= q_left && now_right <= q_right)
        return (tree[pos] % mod);
    ll mid = (now_left + now_right) >> 1;
    push_down(pos, now_left, now_right);
    if (q_left <= mid)
        ans = (query(pos << 1, now_left, mid) + ans) % mod;
    if (q_right > mid)
        ans = (query(pos << 1 | 1, mid + 1, now_right) + ans) % mod;
    return ans % mod;
}
void input()
{
    cin >> n >> m >> mod;
    for (ll i = 1; i <= n; i++)
    {
        scanf("%lld", &datas[i]);
    }
}
void main_work()
{
    build(1, 1, n);
    while (m--)
    {
        ll a;
        scanf("%lld", &a);
        if (a == 1)
        {
            scanf("%lld%lld%lld", &add_left, &add_right, &num);
            mul(1, 1, n);
        }
        else if (a == 2)
        {
            scanf("%lld%lld%lld", &add_left, &add_right, &num);
            add(1, 1, n);
        }
        else
        {
            scanf("%lld%lld", &q_left, &q_right);
            printf("%lld\n", (query(1, 1, n) % mod));
        }
    }
}
int main()
{
    input();
    main_work();
}