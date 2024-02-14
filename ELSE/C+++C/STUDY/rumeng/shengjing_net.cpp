//https://www.luogu.com.cn/problem/P1038
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 10000000
inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
int idx, head[MAX];
struct Node
{
    int to, w, nex;
} edge[MAX];
void add(int u, int v, int w)
{
    edge[++idx] = (Node){v, w, head[u]};
    head[u] = idx;
}
queue<int> q;
int n, p, u[MAX], vis[MAX], jihuo[MAX], dutt[MAX], dutt_chu[MAX];
int c[MAX];
vector<int> s;
void input()
{
    n = read(), p = read();
    int aa, bb, cc;
    for (int i = 1; i <= n; i++)
    {
        aa = read();
        bb = read();
        c[i] = aa;
        u[i] = bb;
        if (aa)
            q.push(i);
    }
    for (int i = 1; i <= p; i++)
    {
        aa = read(), bb = read(), cc = read();
        add(aa, bb, cc);
        dutt_chu[aa]++;
        dutt[bb]++;
    }
    for (int i = 1; i <= n; i++)
    {
        if (!dutt_chu[i])
            s.push_back(i);
    }
}
void tupo()
{
    for (int i = 1; i <= n; i++)
    {
        if (dutt[i])
            c[i] = -u[i];
    }
    while (!q.empty())
    {
        int now = q.front();
        q.pop();
        for (int i = head[now]; i; i = edge[i].nex)
        {
            int to = edge[i].to;
            c[to] += c[now] * edge[i].w;
            dutt[to]--;
            if (!dutt[to] && c[to] > 0)
            {
                q.push(to);
            }
        }
    }
}
void output()
{
    bool flag = false;
    for (int i = 0; i < s.size(); i++)
    {
        if (c[s[i]] > 0)
        {

            printf("%d %d\n", s[i], c[s[i]]);
            flag = true;
        }
    }
    if (!flag)
        printf("NULL");
}
int main()
{
    input();
    tupo();
    output();
}