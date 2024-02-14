// https://www.luogu.com.cn/problem/P1955
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 1000005
struct Node
{
    int x, y, e;
} row[MAX];
int idx, N, n, only[MAX * 2], parent[MAX * 2];
bool cmp(Node a, Node b)
{
    return a.e > b.e;
}
void init()
{
    idx = 0;
    memset(only, 0, sizeof(only));
    memset(parent, 0, sizeof(parent));
}
void init_parent(int x)
{
    for (int i = 1; i <= x; i++)
    {
        parent[i] = i;
    }
}
int fa(int x)
{
    return (x == parent[x]) ? x : parent[x] = fa(parent[x]);
}
void work()
{
    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d%d", &row[i].x, &row[i].y, &row[i].e);
        only[++idx] = row[i].x;
        only[++idx] = row[i].y;
    }

    sort(only + 1, only + 1 + idx);
    int all_nums = unique(only + 1, only + 1 + idx) - only - 1;
    for (int i = 1; i <= n; i++)
    {
        row[i].x = lower_bound(only + 1, only + 1 + all_nums, row[i].x) - only;
        row[i].y = lower_bound(only + 1, only + 1 + all_nums, row[i].y) - only;
    } //离散化

    init_parent(all_nums);
    sort(row + 1, row + 1 + n, cmp);

    for (int i = 1; i <= n; i++)
    {
        int fx = fa(row[i].x), fy = fa(row[i].y);
        if (row[i].e)
        {
            parent[fx] = fy;
        }
        else if (fx == fy)
        {
            printf("NO\n");
            return;
        }
    }
    printf("YES\n");
}
int main()
{
    cin >> N;
    while (N--)
    {
        init();
        work();
    }
}