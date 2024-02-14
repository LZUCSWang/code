#include <bits/stdc++.h>
using namespace std;
#define MAX 10000001
int tree[MAX];
int n, m;
void add(int x, int k)
{
    for (; x <= n; x += x & (-x))
        tree[x] += k;
}
int ask(int x)
{
    int ans = 0;
    for (; x; x -= x & (-x))
        ans += tree[x];
    return ans;
}
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        int t;
        scanf("%d", &t);
        add(i, t);
    }
    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        if (a == 1)
        {
            add(b, c);
        }
        if (a == 2)
        {
            printf("%d\n", ask(c) - ask(b - 1));
        }
    }
}