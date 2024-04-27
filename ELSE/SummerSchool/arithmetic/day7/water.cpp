#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#define MAX 505

int n, m, cnt;
int MAP[MAX][MAX], visits[MAX][MAX];
void input()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            // cin >> MAP[i][j];
            scanf("%d", &MAP[i][j]);
        }
    }
}
pair<int, int> dir[4] = {
    {0, 1},
    {1, 0},
    {0, -1},
    {-1, 0}};
void flood(int x, int y)
{
    visits[x][y] = 1;
    for (int i = 0; i < 4; i++)
    {
        int nx = x + dir[i].first;
        int ny = y + dir[i].second;
        if (nx < 1 || nx > n || ny < 1 || ny > m || visits[nx][ny])
            continue;
        if (MAP[nx][ny] < MAP[x][y])
            flood(nx, ny);
    }
}
// 2 5
// 9 1 5 4 3
// 8 7 6 1 2
void printf_MAP()
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            printf("%d ", MAP[i][j]);
        }
        printf("\n");
    }
}
void printf_visits()
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            printf("%d ", visits[i][j]);
        }
        printf("\n");
    }
}
struct item
{
    int left, right;
} line[MAX];
void all_search()
{
    for (int j = 1; j <= m; j++)
    {
        flood(1, j);
    }
    for (int j = 1; j <= m; j++)
    {
        if (visits[n][j])
        {
            cnt++;
        }
    }
    if (cnt != m)
    {
        printf("0\n%d\n", m - cnt);
        // return 0;
        exit(0);
    }
    printf("1\n");
}
void add_line()
{
    for (int j = 1; j <= m; j++)
    {
        memset(visits, 0, sizeof(visits));
        flood(1, j);
        bool flag = false;
        for (int k = 1; k <= m + 1; k++)
        {
            if (visits[n][k] && !flag)
            {
                line[j].left = k;
                flag = true;
                // break;
            }
            if (visits[n][k] == 0 && flag)
            {
                line[j].right = k - 1;
                break;
            }
        }
    }
}
bool cmp(item a, item b)
{
    return a.right < b.right;
}
void count_mins()
{
    sort(line + 1, line + m + 1, cmp);
    int have_right = 0, index_i = 0, index = 0, cnt = 0, max_right;
    while (have_right < m)
    {
        max_right = 0;
        for (int i = index + 1; i <= m; i++)
        {
            if (line[i].right > max_right && line[i].right > have_right && line[i].left <= have_right + 1)
            {
                max_right = line[i].right;
                index_i = i;
            }
        }
        index = index_i;
        have_right = max_right;
        cnt++;
    }
    printf("%d\n", cnt);
}
void print_line()
{
    for (int i = 1; i <= m; i++)
    {
        printf("%d %d\n", line[i].left, line[i].right);
    }
}
int main()
{
    input();
    // flood(1, 2);
    all_search();
    add_line();
    count_mins();
    // print_line();

    // printf_visits();
}