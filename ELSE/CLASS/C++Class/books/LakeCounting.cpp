#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
#define MAX 100000
char yard[100][100];
int n, m;
void dfs(int x, int y)
{
    yard[x][y] = '.';
    for (int dx = -1; dx <= 1; dx++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && yard[nx][ny] == 'W')
            {
                dfs(nx, ny);
            }
        }
    }
}
int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> yard[i][j];
        }
    }
    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (yard[i][j] == 'W')
            {
                dfs(i, j);
                cnt++;
            }
        }
    }
    cout << cnt << endl;
}