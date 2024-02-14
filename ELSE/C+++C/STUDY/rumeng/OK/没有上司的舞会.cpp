// https://www.luogu.com.cn/problem/P1352
#include <bits/stdc++.h>
#include <iostream>
using namespace std;
#define ll long long
#define MAX 6005
// 7
// 1
// 1
// 1
// 1
// 1
// 1
// 1
// 1 3
// 2 3
// 6 4
// 7 4
// 4 5
// 3 5
int n, w[MAX], vis[MAX], f[MAX][2];
vector<int> son[MAX];
void input()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", w + i);
    }
    for (int i = 1; i <= n - 1; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        son[b].push_back(a);
        vis[a] = 1;
    }
}
void dfs(int now)
{
    f[now][1] = w[now];
    f[now][0] = 0;
    for (int i = 0; i < son[now].size(); i++)
    {
        int to = son[now][i];
        dfs(to);
        f[now][0] += max(f[to][0], f[to][1]);
        f[now][1] += f[to][0];
    }
}
int main()
{
    input();
    int root;
    for (int i = 1; i <= n; i++)
    {
        if (!vis[i])
        {
            root = i;
            break;
        }
    }
    dfs(root);
    printf("%d", max(f[root][0], f[root][1]));
}