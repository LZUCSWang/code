#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#define MAX 5000005
#define MAX_POINT 505
int n, m, c_num;
int indexs;
int nn;
int head[MAX_POINT];
int visits[MAX_POINT];
int colors[MAX_POINT];
set<int> colors_set;
queue<int> q;
struct node
{
    int to, next;
} edges[MAX];
void add(int u, int v)
{
    edges[++indexs].to = v;
    edges[indexs].next = head[u];
    head[u] = indexs;
}
bool bfs_(int from_)
{
    q.push(from_);
    while (!q.empty())
    {
        int from = q.front();
        q.pop();
        visits[from] = 1;
        for (int i = head[from]; i; i = edges[i].next)
        {
            int to = edges[i].to;
            if (visits[to])
                continue;
            if (colors[to] == colors[from])
            {
                printf("No\n");
                return false;
            }
            q.push(to);
        }
    }
    return true;
    // printf("Yes\n");
}
void bfs()
{
    for (int i = 1; i <= n; i++)
    {
        if (visits[i])
            continue;
        if (!bfs_(i))
        {
            return;
        }
    }
    printf("Yes\n");
}
void judges()
{
    memset(colors, 0, sizeof(colors));
    memset(visits, 0, sizeof(visits));
    colors_set.clear();
    for (int i = 1; i <= n; i++)
    {
        int c;
        cin >> c;
        if (!colors_set.count(c))
        {
            colors_set.insert(c);
            if (colors_set.size() > c_num)
            {
                printf("No\n");
                return;
            }
        }
        colors[i] = c;
    }
    if (colors_set.size() != c_num)
    {
        printf("No\n");
        return;
    }
    bfs();
}
void judges_all()
{
    cin >> nn;
    for (int i = 1; i <= nn; i++)
    {
        judges();
    }
}
void input()
{
    cin >> n >> m >> c_num;
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        add(u, v);
        add(v, u);
    }
}
int main()
{
    input();
    judges_all();
    return 0;
}