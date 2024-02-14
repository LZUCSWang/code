#include <bits/stdc++.h>
using namespace std;
#define MAXN 1005
typedef long long ll;
int hurt[MAXN][MAXN], n, m;
typedef pair<int, int> pos;
queue<pos> q;
bool visits[MAXN][MAXN];
int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
bool check(int x)
{
    memset(visits, false, sizeof(visits));
    while (!q.empty())
    {
        q.pop();
    }
    for (int j = 1; j <= m; j++)
    {
        if (hurt[2][j] <= x)
        {
            q.push({2, j});
            visits[2][j] = true;
        }
    }
    while (!q.empty())
    {
        pos p = q.front();
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            int nx = p.first + dir[i][0], ny = p.second + dir[i][1];
            if (nx < 1 || nx > n || ny < 1 || ny > m || visits[nx][ny] || hurt[nx][ny] > x)
            {
                continue;
            }
            if (nx == n)
            {
                return true;
            }
            q.push({nx, ny});
            visits[nx][ny] = true;
        }
    }
    return false;
}
int main()
{
    // ios::sync_with_stdio(false);

    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            scanf("%d", &hurt[i][j]);
        }
    }
    int l = 1, r = 1000;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
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