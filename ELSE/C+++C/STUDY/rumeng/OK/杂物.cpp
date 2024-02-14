// https://www.luogu.com.cn/problem/P1113
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 10001
int n, dutt[MAX], ans[MAX], far[MAX];
vector<int> G[MAX];
void input()
{
    cin >> n;
    int t, len, pre;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &t, far + i);
        while (true)
        {
            scanf("%d", &pre);
            if (pre == 0)
            {
                break;
            }
            dutt[t]++;
            G[pre].push_back(t);
        }
    }
}
queue<int> q;
void bfs()
{
    for (int i = 1; i <= n; i++)
    {
        if (dutt[i] == 0)
        {
            q.push(i);
            ans[i] = far[i];
        }
    }
    while (!q.empty())
    {
        int t = q.front();
        q.pop();
        for (int i = 0; i < G[t].size(); i++)
        {
            int to = G[t][i];
            dutt[to]--;
            ans[to] = max(ans[to], ans[t] + far[to]);
            if (!dutt[to])
            {
                q.push(to);
            }
        }
    }
}
int main()
{
    int t = 0;
    input();
    bfs();
    for (int i = 1; i <= n; i++)
    {
        t = max(t, ans[i]);
    }
    printf("%d", t);
}