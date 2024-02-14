// https://www.luogu.com.cn/problem/P3956
#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 1000

// 5 7
// 1 1 0
// 1 2 0
// 2 2 1
// 3 3 1
// 3 4 0
// 4 4 1
// 5 5 0
int n, m;
int maze[MAX][MAX];
int coss[MAX][MAX];
void input()
{
    scanf("%d%d", &m, &n);
    for (int i = 1, x, y, c; i <= n; i++)
    {
        scanf("%d%d%d", &x, &y, &c);
        maze[x][y] = (c == 0) ? 2 : c;
    }
}

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};
int vis[MAX][MAX];
int ans;

void dfs(int x, int y, int cost, int flag, int color)
{
    if (cost >= ans)
    {
        return;
    }
    if (x == m && y == m)
    {
        ans = cost;
        return;
    }
    for (int i = 0; i < 4; i++)
    {
        int nx = x + dx[i], ny = y + dy[i];
        if (nx < 1 || nx > m || ny < 1 || ny > m || vis[nx][ny])
            continue;
        if (maze[nx][ny] == 0)
        {
            if (!flag && coss[nx][ny] > cost + 2)
            {
                vis[nx][ny] = 1;
                coss[nx][ny] = cost + 2;
                dfs(nx, ny, cost + 2, 1, maze[x][y]);
                vis[nx][ny] = 0;
            }
        }
        else
        {
            int costtt = cost;
            if (maze[nx][ny] != color)
                costtt++;
            if (coss[nx][ny] > costtt)
            {
                coss[nx][ny] = costtt;
                vis[nx][ny] = 1;
                dfs(nx, ny, costtt, 0, maze[nx][ny]);
                vis[nx][ny] = 0;
            }
        }
    }
}
int main()
{
    input();
    ans = INF;
    vis[1][1] = 1;
    memset(coss, 0x3f3f3f, sizeof(coss));
    coss[1][1] = 0;
    dfs(1, 1, 0, 0, maze[1][1]);
    printf("%d", (ans == INF) ? -1 : ans);
}