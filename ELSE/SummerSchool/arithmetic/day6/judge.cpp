#include <bits/stdc++.h>
using namespace std;
#define MAX 10005
#define lli long long int
#define MAX_EDGE 1000005
struct node
{
    lli a, b, d;
} edges[MAX_EDGE];
bool cmp(node a, node b)
{
    return a.d < b.d;
}
bool flag[MAX];
lli dis_set[MAX][MAX], parent[MAX];
set<lli> s;
lli find_set(lli x)
{
    lli r = x, i = x, j;
    while (parent[r] != r)
        r = parent[r];
    while (i != r)
    {
        j = parent[i];
        parent[i] = r;
        i = j;
    }
    return r;
}
int main()
{
    lli n, m, ans = 0, a, b, d, cnt = 0, i, fa, fb, j, k, t; //边的数量
    cin >> n >> m;
    for (i = 0; i < m; i++)
        scanf("%d %d %d", &edges[i].a, &edges[i].b, &edges[i].d);
    for (i = 1; i <= n; i++)
        parent[i] = i;
    sort(edges, edges + m, cmp);
    for (i = 0; i < m; i++)
    {
        fa = find_set(edges[i].a);
        fb = find_set(edges[i].b);
        if (fa != fb)
        {
            for (j = 1; j <= n; j++)
            {
                if (find_set(j) == fa)
                {
                    for (k = 1; k <= n; k++)
                    {
                        if (find_set(k) == fb)
                        {
                            dis_set[j][k] = dis_set[k][j] = edges[i].d;
                        }
                    }
                }
            }
            flag[i] = true;
            parent[fa] = fb;
            ans += edges[i].d;
            cnt++;
        }
    }
    if (cnt < n - 1)
    {
        ans = 0;
        cout << "No MST" << endl; //如果不是最小生成树，则不能构成图
        for (i = 1; i <= n; i++)
        {
            t = find_set(i);
            if (s.count(t) == 0)
            {
                s.insert(t);
                ans++;
            }
        }
        cout << ans << endl;
        return 0;
    }
    cout << ans << endl;
    for (i = 0; i < m; i++)
    {
        if (!flag[i])
        {
            if (dis_set[edges[i].a][edges[i].b] == edges[i].d)
            {
                printf("No");
                return 0;
            }
        }
    }
    printf("Yes");
    return 0;
}