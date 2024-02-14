#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 10000001
#define nMAX 1001
int ans[MAX];
int seen[MAX];
typedef struct Node
{
    int to, dis;
    bool operator<(Node p) const
    {
        return dis > p.dis;
    }
} Node;
int datas[nMAX][nMAX];
int n, m;
void build(int u, int v, int w)
{
    if (datas[u][v] == 0 || datas[u][v] > w)
    {
        datas[u][v] = w;
    }
}
void input()
{
    cin >> n >> m;
    while (m--)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        build(u, v, w);
    }
}
void init_ans()
{
    memset(ans, -1, sizeof(ans));
}
void diji()
{
    priority_queue<Node> q;
    Node t;
    memset(seen, 0, sizeof(seen));
    t.dis = 0;
    ans[1] = 0;
    t.to = 1;
    q.push(t);
    while (!q.empty())
    {
        t = q.top();

        q.pop();
        int from = t.to;
        int from_dis = t.dis;
        if (seen[from])
        {
            continue;
        }
        seen[from] = 1;
        for (int to = 1; to <= n; to++)
        {
            if (to != from && datas[from][to] != 0 && (ans[to] == -1 || ans[to] > from_dis + datas[from][to]))
            {
                ans[to] = from_dis + datas[from][to];
                t.dis = ans[to];
                t.to = to;
                q.push(t);
            }
        }
    }
}
ll sum = 0;
void counts()
{
    for (int i = 2; i <= n; i++)
    {
        sum += ans[i];
        ans[i] = -1;
    }
}
void reverse()
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            swap(datas[i][j], datas[j][i]);
        }
    }
}
int main()
{
    input();
    init_ans();
    diji();
    counts();
    reverse();
    diji();
    counts();
    cout << sum << endl;
}