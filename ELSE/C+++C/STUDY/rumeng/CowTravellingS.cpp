#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 10000001
char mapp[105][105];
int cnt[105][105][18];
int n, m, t, sx, sy, ex, ey, nows_x, nows_y, nows_t, new_x, new_y, new_t;
int dir_x[] = {0, 1, 0, -1}, dir_y[] = {1, 0, -1, 0};
struct Node
{
    int x, y, t;
};
queue<Node> q;
void bfs()
{
    q.push((Node){sx, sy, 0});
    cnt[sx][sy][0] = 1;
    while (!q.empty())
    {
        Node temp = q.front();
        q.pop();
        nows_x = temp.x, nows_y = temp.y, nows_t = temp.t;
        for (int i = 0; i < 4; i++)
        {
            new_x = nows_x + dir_x[i], new_y = nows_y + dir_y[i], new_t = nows_t + 1;
            if (cnt[new_x][new_y][new_t])
            {
                cnt[new_x][new_y][new_t] += cnt[nows_x][nows_y][nows_t];
            }
            else if (new_x >= 1 && new_x <= n && new_y >= 1 && new_y <= m && mapp[new_x][new_y] == '.' && new_t <= t)
            {

                cnt[new_x][new_y][new_t] += cnt[nows_x][nows_y][nows_t];
                q.push((Node){new_x, new_y, new_t});
            }
        }
    }
    printf("%d", cnt[ex][ey][t]);
}
void input()
{
    cin >> n >> m >> t;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> mapp[i][j];
        }
    }
    cin >> sx >> sy >> ex >> ey;
}
int main()
{
    input();
    bfs();
}