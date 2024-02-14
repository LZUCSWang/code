#include <bits/stdc++.h>
// https://www.luogu.com.cn/problem/P1522
using namespace std;
#define ll long long
#define MAX 155
#define INF 1e20
int n;
char t;
struct point
{
    int x, y;
} points[MAX];
double dis[MAX][MAX];
double distan(int x, int y)
{
    return sqrt(pow(points[x].x - points[y].x, 2) + pow(points[x].y - points[y].y, 2));
}
void init_dis()
{
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            dis[i][j] = INF;
}
void floyd()
{
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (dis[i][j] > dis[i][k] + dis[k][j])
                    dis[i][j] = dis[i][k] + dis[k][j];
}
void input()
{
    scanf("%d\n", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &points[i].x, &points[i].y);
    init_dis();
    for (int i = 1; i <= n; i++)
    {
        getchar();
        for (int j = 1; j <= n; j++)
        {
            t = getchar();
            if (t == '1')
                dis[i][j] = distan(i, j);
            else if (i == j)
                dis[i][j] = 0;
        }
    }
    floyd();
}
int colors[MAX];
void dfs(int now, int color)
{
    colors[now] = color;
    for (int i = 1; i <= n; i++)
        if (!colors[i] && dis[now][i] < INF)
            dfs(i, color);
}

void put_colors()
{
    int color = 0;
    for (int i = 1; i <= n; i++)
        if (!colors[i])
            dfs(i, ++color);
}
double max_pos[MAX] = {0.0}, diameter[MAX] = {0.0};
void find_min_max()
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            if (dis[i][j] < INF)
                max_pos[i] = max(max_pos[i], dis[i][j]);
        diameter[colors[i]] = max(diameter[colors[i]], max_pos[i]);
    }
}
double ans = INF;
void find_ans()
{
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            if (colors[i] != colors[j])
                ans = min(ans, max(max(diameter[colors[i]], diameter[colors[j]]), (max_pos[i] + max_pos[j] + distan(i, j))));
    printf("%.6f\n", ans);
}
int main()
{
    input();
    put_colors();
    find_min_max();
    find_ans();
}