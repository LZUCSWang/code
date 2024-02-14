#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 10000000
// https://www.luogu.com.cn/problem/P1726
// 5 5
// 1 2 1
// 1 3 2
// 2 4 2
// 5 1 2
// 3 5 1
int n, m;
int dfn[MAX], low[MAX], cnt, tim, belong[MAX], nums[MAX], min_idx = INF;
bool vis[MAX];
int max_temp, ans_cnt;
stack<int> st;
int head[MAX], idx;
struct Node
{
    int to, nex;
} edge[MAX];
void add(int u, int v)
{
    edge[++idx] = Node{v, head[u]};
    head[u] = idx;
}
void tarjan(int now)
{
    dfn[now] = low[now] = ++tim;
    vis[now] = true;
    st.push(now);
    for (int i = head[now]; i; i = edge[i].nex)
    {
        int to = edge[i].to;
        if (!dfn[to])
        {
            tarjan(to);
            low[now] = min(low[now], low[to]);
        }
        else if (vis[to])
        {
            low[now] = min(low[now], dfn[to]);
        }
    }
    int temp = 0, temp_min_idx = INF;
    if (low[now] == dfn[now])
    {
        belong[now] = ++cnt;
        temp++;
        vis[now] = false;
        temp_min_idx = min(temp_min_idx, now);
        while (st.top() != now)
        {
            temp_min_idx = min(temp_min_idx, st.top());
            belong[st.top()] = cnt;
            vis[st.top()] = false;
            st.pop();
            temp++;
            /* code */
        }
        st.pop();
        if (temp > max_temp || temp == max_temp && temp_min_idx < min_idx)
        {
            max_temp = temp;
            min_idx = temp_min_idx;
            ans_cnt = cnt;
        }
    }
}
void input()
{
    cin >> n >> m;
    for (int i = 1, u, v, w; i <= m; i++)
    {
        scanf("%d%d%d", &u, &v, &w);
        add(u, v);
        if (w == 2)
            add(v, u);
    }
}
int main()
{
    input();
    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            tarjan(i);
    printf("%d\n", max_temp);
    for (int i = min_idx; i <= MAX; i++)
    {
        if (belong[i] == ans_cnt)
        {
            printf("%d ", i);
        }
    }
}