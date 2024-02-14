#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000010;
int tot;
int k[MAXN];
string s;
string T;
int n, m;
struct node
{
    char ch;
    bool endflag;
    int link[30];
} tree[MAXN];
void add(int k, int node)
{
    int chindex = s[k] - 'a';
    if (!tree[node].link[chindex])
    {
        tree[node].link[chindex] = ++tot;
        tree[tot].ch = s[k];
    }
    int nextnode = tree[node].link[chindex];
    if (k == s.size() - 1)
    {
        tree[nextnode].endflag = true;
        return;
    }
    add(k + 1, nextnode);
}
void find(int p)
{
    int len = T.size();
    int ans;
    k[0] = p;
    for (int i = 0; i <= len; ++i)
    {
        if (k[i] != p)
            continue;
        else
            ans = i;
        for (int now = 0, j = i; j <= len; ++j)
        {
            int chindex = T[j] - 'a';
            if (tree[now].endflag)
                k[j] = p;
            now = tree[now].link[chindex];
            if (!now)
                break;
        }
    }

    printf("%d\n", ans);
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        cin >> s;
        add(0, 0);
    }
    for (int i = 1; i <= m; ++i)
    {
        cin >> T;
        find(i);
    }
    return 0;
}