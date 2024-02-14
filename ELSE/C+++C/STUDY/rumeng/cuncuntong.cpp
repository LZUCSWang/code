#include <bits/stdc++.h>
using namespace std;
#define MAX 10000001
int n, m;
int parent[MAX];
int fa(int x)
{
    return x == parent[x] ? x : parent[x] = fa(parent[x]);
}

void init()
{
    for (int i = 1; i <= n; i++)
    {
        parent[i] = i;
    }
}
void input()
{
    init();
    int cnt = 0;
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        int fx = fa(u), fy = fa(v);
        if (fx != fy)
        {
            parent[fx] = fy;
        }
    }
    for (int i = 1; i < n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            int fx = fa(i), fy = fa(j);
            if (fx != fy)
            {
                parent[fx] = fy;
                cnt++;
            }
        }
    }
    printf("%d\n", cnt);
}
int main()
{
    while (true)
    {
        scanf("%d", &n);
        if (n == 0)
        {
            return 0;
        }
        scanf("%d", &m);
        input();
    }
}