#include <bits/stdc++.h>
using namespace std;
#define MAX 1000005
int k, pre[MAX], fathers[MAX], size_sub[MAX], ans[MAX];
struct node
{
    int to, next;
} edges[MAX];
void add(int x, int y)
{
    k++;
    edges[k].to = y;
    edges[k].next = pre[x];
    pre[x] = k;
}
int dfs(int son, int father)
{
    fathers[son] = father;
    size_sub[son] = 1;
    for (int i = pre[son]; i; i = edges[i].next)
    {
        int to = edges[i].to;
        if (to != father)
        {
            size_sub[son] += dfs(to, son);
        }
    }
    return size_sub[son];
}
bool seen[MAX];
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        add(x, y);
        add(y, x);
    }
    dfs(1, 0);
    // for (int i = 1; i <= n; i++)
    // {
    //     cout << size_sub[i] << " ";
    // }
    // cout << endl;
    for (int i = 1; i <= n; i++)
    {
        ans[i] = n - size_sub[i];
        for (int j = pre[i]; j; j = edges[j].next)
        {
            if (fathers[edges[j].to] == i)
                ans[i] = max(ans[i], size_sub[edges[j].to]);
        }
    }
    int min_ans = n, min_data = MAX;
    for (int i = 1; i <= n; i++)
    {
        if (ans[i] < min_data)
        {
            min_data = ans[i];
            min_ans = i;
        }
        // cout << ans[i] << " ";
    }
    cout << min_ans << endl;
    //计算距离
    int dis = 0;
    queue<pair<int, int>> q;
    q.push(make_pair(min_ans, 0));
    seen[min_ans] = true;
    while (!q.empty())
    {
        auto now_item = q.front();
        q.pop();
        int now = now_item.first;
        int now_dis = now_item.second;
        for (int i = pre[now]; i; i = edges[i].next)
        {
            int to = edges[i].to;
            if (!seen[to])
            {
                seen[to] = true;
                q.push(make_pair(to, now_dis + 1));
                dis += now_dis+1;
            }
        }
    }
    cout << dis << endl;
}