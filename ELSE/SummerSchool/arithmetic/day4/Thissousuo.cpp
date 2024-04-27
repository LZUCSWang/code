#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int inf = 0x3f3f3f3f;
const int maxn = 1010;
int n, flag;
int pr[maxn];

vector<int> v;

void find(int l, int r)
{
    if (l > r)
        return;
    int tl = l + 1, tr = r;
    if (!flag)
    {
        while (tl <= r && pr[tl] < pr[l])
            tl++;
        while (tr > l && pr[tr] >= pr[l])
            tr--;
    }
    else
    {
        while (tl <= r && pr[tl] >= pr[l])
            tl++;
        while (tr > l && pr[tr] < pr[l])
            tr--;
    }
    if (tl - tr != 1)
        return;
    find(l + 1, tr);
    find(tl, r);
    v.push_back(pr[l]);
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &pr[i]);
    find(0, n - 1);
    if (v.size() != n)
    {
        flag = 1;
        v.clear();
        find(0, n - 1);
    }
    if (v.size() != n)
        printf("NO\n");
    else
    {
        printf("YES\n");
        for (int i = 0; i < n; i++)
        {
            printf("%d%c", v[i], i == (n - 1) ? '\n' : ' ');
        }
    }
    return 0;
}
