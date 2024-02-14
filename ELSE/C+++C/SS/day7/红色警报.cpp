#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#define MAX 3000005

int parent[MAX], flag[MAX], target_point[MAX];
int n, m, k;

int count_my()
{
    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
        if (parent[i] == i)
        {
            cnt++;
        }
    }
    return cnt;
}

void init_my()
{
    for (int i = 0; i < n; i++)
    {
        parent[i] = i;
    }
}

struct node
{
    int from, to;
} edge[MAX];
// 5 4
// 0 1
// 1 3
// 3 0
// 0 4
// 5
// 1 2 0 4 3

int find_my(int x)
{
    return x == parent[x] ? x : parent[x] = find_my(parent[x]);
}

void merge_my(int x, int y)
{
    int fx = find_my(x), fy = find_my(y);
    parent[fx] = fy;
}

int main()
{
    cin >> n >> m;
    init_my();
    for (int i = 1; i <= m; i++)
    {
        cin >> edge[i].from >> edge[i].to;
        merge_my(edge[i].from, edge[i].to);
    }
    int T_1 = count_my();
    cin >> k;
    for (int i = 1; i <= k; i++)
    {
        cin >> target_point[i];
        flag[target_point[i]] = 1;
        init_my();
        for (int j = 1; j <= m; j++)
        {
            if (!flag[edge[j].from] && !flag[edge[j].to])
            {
                merge_my(edge[j].from, edge[j].to);
            }
        }
        int T_2 = count_my();
        if (T_1 + 1 == T_2 || T_1 == T_2)
        {
            printf("City %d is lost.\n", target_point[i]);
        }
        else
        {
            printf("Red Alert: City %d is lost!\n", target_point[i]);
        }
        T_1 = T_2;
    }
    if (k == n)
    {
        printf("Game Over.");
    }
}