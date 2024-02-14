#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 5005
// 5 7
// 1 2
// 1 3
// 2 3
// 3 5
// 2 5
// 4 5
// 3 4
#define mod 80112002
vector<int> G[MAX];
int n, m, ans[MAX], dutt[MAX];
void input()
{
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        dutt[b]++;
        G[a].push_back(b);
    }
}
int sum;
queue<int> q;
void work()
{
    for (int i = 1; i <= n; i++)
    {
        if (dutt[i] == 0)
        {
            q.push(i);
            ans[i] = 1;
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
            ans[to] += ans[t];
            ans[to] %= mod;
            if (dutt[to] == 0)
            {
                q.push(to);
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        if (G[i].size() == 0)
        {
            sum = (sum + ans[i]) % mod;
        }
    }
    printf("%d", sum % mod);
}
int main()
{
    input();
    work();
}