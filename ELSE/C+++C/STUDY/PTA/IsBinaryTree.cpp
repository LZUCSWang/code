#include <bits/stdc++.h>
using namespace std;
#define MAXN 100000
int a[MAXN];
int n;
vector<int> ans;
bool flag = false;
void find(int l, int r)
{
    if (l > r)
        return;
    int tl = l + 1, tr = r;
    if (!flag)
    {
        while (tl <= r && a[tl] < a[l])
            tl++;
        while (tr >= l + 1 && a[tr] >= a[l])
            tr--;
    }
    else
    {
        while (tl <= r && a[tl] >= a[l])
            tl++;
        while (tr >= l + 1 && a[tr] < a[l])
            tr--;
    }
    if (tl - tr != 1)
        return;
    find(l + 1, tr);
    find(tl, r);
    ans.push_back(a[l]);
}
int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", a + i);
    }
    find(0, n - 1);
    if (ans.size() != n)
    {
        flag = 1;
        ans.clear();
        find(0, n - 1);
    }
    if (ans.size() != n)
        printf("NO\n");
    else
    {
        printf("YES\n");
        for (int i = 0; i < n; i++)
        {
            printf("%d%c", ans[i], i == (n - 1) ? '\n' : ' ');
        }
    }
}