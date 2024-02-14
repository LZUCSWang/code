// https://www.luogu.com.cn/problem/P1902
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 10000001
int n, m, datas[1001][1001];
void input()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            scanf("%d", &datas[i][j]);
        }
    }
}
int dir_x[] = {0, 1, 0, -1}, dir_y[] = {1, 0, -1, 0};
int vis[1001][1001];
queue<pair<int, int>> q;
void init()
{
    while (!q.empty())
        q.pop();
    memset(vis, 0, sizeof(vis));
}
bool judge(int xx)
{
    init();
    int ans = 0;
    for (int j = 1; j <= m; j++)
    {
        if (datas[2][j] <= xx)
        {
            q.push({2, j});
            vis[2][j] = 1;
        }
    }
    while (!q.empty())
    {
        pair<int, int> t = q.front();
        q.pop();
        int x = t.first, y = t.second;
        for (int i = 0; i <= 4; i++)
        {
            int nx = x + dir_x[i], ny = y + dir_y[i];
            if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && vis[nx][ny] == 0 && datas[nx][ny] <= xx)
            {
                vis[nx][ny] = 1;
                q.push({nx, ny});
                if (nx == n)
                {
                    ans++;
                    if (ans == m)
                    {
                        return true;
                    }
                }
            }
        }
    }
    if (ans == m)
    {
        return true;
    }
    return false;
}
int main()
{
    input();
    int l = 1, r = 1000;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (judge(mid))
        {
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }
    printf("%d", l);
}