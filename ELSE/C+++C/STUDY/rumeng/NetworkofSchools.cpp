#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 10000
#define ll long long

int head[MAX], idx;
struct Node
{
    int from, to, nex;
} edge[MAX];
void add(int u, int v)
{
    edge[++idx] = Node{u, v, head[u]};
    head[u] = idx;
}

int n, m;
// 5
// 2 4 3 0
// 4 5 0
// 0
// 0
// 1 0

void input()
{
    cin >> n;
    for (int i = 1, t; i <= n; i++)
        while (true)
        {
            scanf("%d", &t);
            if (t == 0)
                break;
            add(i, t);
        }
}

int dfn[MAX], low[MAX], cnt, tim, belong[MAX];
bool vis[MAX];
stack<int> st;
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
            low[now] = min(low[now], dfn[to]);
    }
    if (dfn[now] == low[now])
    {
        belong[now] = ++cnt;
        vis[now] = false;
        while (st.top() != now)
        {
            belong[st.top()] = cnt;
            vis[st.top()] = false;
            st.pop();
        }
        st.pop();
    }
}
int ru[MAX], chu[MAX];
void rubuild()
{
    for (int i = 1; i <= idx; i++)
        if (belong[edge[i].from] != belong[edge[i].to])
        {
            chu[belong[edge[i].from]]++;
            ru[belong[edge[i].to]]++;
        }
}

int main()
{
    input();
    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            tarjan(i);
    if (cnt == 1)
    {
        printf("1\n0");
        return 0;
    }
    rubuild();
    ll ansa = 0, ansb = 0;

    for (int i = 1; i <= cnt; i++)
    {
        if (ru[i] == 0)
            ansa++;
        if (chu[i] == 0)
            ansb++;
    }
    printf("%lld\n%lld", ansa, max(ansa, ansb));
 }
