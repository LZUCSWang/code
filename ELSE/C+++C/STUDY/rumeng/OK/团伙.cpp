// https://www.luogu.com.cn/problem/P1892
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 1005
int parent[MAX], a, b, e[MAX], m, n;
char flag;
int countt[MAX], ans = 0;
int fa(int x)
{
    return (x == parent[x]) ? x : parent[x] = fa(parent[x]);
}
void merge(int a, int b)
{
    int fx = fa(a), fy = fa(b);
    if (fx != fy)
        parent[fx] = fy;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        parent[i] = i;
    while (m--)
    {
        cin >> flag >> a >> b;
        if (flag == 'F')
            merge(a, b);
        else
        {
            if (!e[a])
                e[a] = fa(b);
            else
                merge(e[a], b);
            if (!e[b])
                e[b] = fa(a);
            else
                merge(e[b], a);
        }
    }
    for (int i = 1; i <= n; i++)
        countt[fa(i)] = 1;
    for (int i = 1; i <= n; i++)
        if (countt[i])
            ans++;
    printf("%d", ans);
}