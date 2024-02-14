#include <bits/stdc++.h>
using namespace std;
#define MAX 1000010
int tot, nodes[MAX], n, m, finda_ans, len, chindex, nextnode;
string s, T;
struct node
{
    char ch;
    int endflag;
    int link[30];
} tree[MAX];
int get_int(char ch)
{
    return ch - 'a';
}
void add(int pos, int node)
{
    chindex = get_int(s[pos]);
    if (!tree[node].link[chindex])
    {
        tree[node].link[chindex] = ++tot;
        tree[tot].ch = s[pos];
    }
    nextnode = tree[node].link[chindex];
    if (pos + 1 == s.size())
    {
        tree[nextnode].endflag = 1;
        return;
    }
    add(pos + 1, nextnode);
}
void deal(int p)
{
    for (int i = 0; i <= len; ++i)
    {
        if (nodes[i] != p)
            continue;
        else
            finda_ans = i;
        for (int now = 0, j = i; j <= len; ++j)
        {
            chindex = T[j] - 'a';
            if (tree[now].endflag)
                nodes[j] = p;
            now = tree[now].link[chindex];
            if (!now)
                break;
        }
    }
}
void input()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        cin >> s;
        int pos_s = 0, node_s = 0;
        add(pos_s, node_s);
    }
}
void main_work()
{
    for (int i = 1; i <= m; ++i)
    {
        cin >> T;
        nodes[0] = i;
        len = T.size();
        deal(i);
        printf("%d\n", finda_ans);
    }
}
int main()
{
    input();
    main_work();
    return 0;
}