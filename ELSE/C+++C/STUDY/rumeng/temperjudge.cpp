#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e5 + 10;
struct EDGE
{
    int to, next;
    ll w;
} e[maxn << 1];
bool nl[maxn]; // not leaf
int n, m, k, root, cnt, dep[maxn], fa[maxn][22], Log2[maxn], head[maxn];
ll dis[maxn], s[maxn];
void add(int u, int v, ll w)
{
    e[++cnt] = (EDGE){v, head[u], w};
    head[u] = cnt;
}
inline void dfs(int u, int f) // LAC dfs
{
    dep[u] = dep[f] + 1;
    fa[u][0] = f;
    for (int i = 1; (1 << i) <= dep[u]; i++)
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (int i = head[u]; i; i = e[i].next)
    {
        if (e[i].to != f)
            nl[u] = 1,
            dis[e[i].to] = dis[u] + e[i].w, dfs(e[i].to, u);
    }
}
inline int LCA(int x, int y)
{
    if (dep[x] < dep[y])
        swap(x, y);
    while (dep[x] > dep[y]) 
        x = fa[x][Log2[dep[x] - dep[y]] - 1];
    if (x == y)
        return x;
    for (int k = Log2[dep[x]] - 1; k >= 0; k--)
        if (fa[x][k] != fa[y][k])
            x = fa[x][k], y = fa[y][k];
    return fa[x][0];
}
int st[maxn], tot;     // st[]:存叶子几点的编号
inline void DFS(int u) //找到所有叶子结点
{
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != fa[u][0])
            DFS(e[i].to);
    if (!nl[u])
        st[++tot] = u;
}
inline ll calc(int u, int v)
{
    return s[v] + dis[st[v]] - s[u] + dis[st[u]];
}
inline int erfen(int s, ll x) //对能走到的位置二分
{
    int L = s, R = tot, res = s - 1;
    while (L <= R)
    {
        int mid = (L + R) >> 1;
        if (calc(s, mid) <= x)
            res = mid, L = mid + 1;
        else
            R = mid - 1; 
    }
    return res;
}
inline bool check(ll x)
{
    int last = 0, temp = 0;
    for (int i = 1; i <= k; i++)
    {
        temp = erfen(last + 1, x);
        if (temp == last)
            return 0;
        if (temp >= tot)
            return 1;
        last = temp;
    }
    return temp == tot;
}
int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1, x, y, w; i < n; i++)
    {
        scanf("%d%d%d", &x, &y, &w);
        add(x, y, w);
        add(y, x, w);
    }
    dfs(1, 0);
    DFS(1);
    for (int i = 1; i <= n; i++)
        Log2[i] = Log2[i - 1] + (1 << Log2[i - 1] == i);
    for (int i = 2; i <= tot; i++) //求解s数组
        s[i] = s[i - 1] + dis[st[i]] + dis[st[i - 1]] - dis[LCA(st[i - 1], st[i])] * 2LL;
    ll l = 1, r = 1LL << 60, ans = 1LL << 60;
    while (l <= r)
    { //对答案二分
        ll mid = (l + r) >> 1;
        if (check(mid))
            ans = mid, r = mid - 1;
        else
            l = mid + 1;
    }
    printf("%lld", ans);
    return 0;
}