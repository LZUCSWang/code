#include <bits/stdc++.h>
#define MAX 1001
using namespace std;
int n, m, cha[MAX][MAX];
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        for (int p = x1; p <= x2; p++)
        {
            cha[p][y1]++;
            cha[p][y2 + 1]--;
        }
    }
    // for (int i = 1; i <= n; i++)
    // {
    //     for (int j = 1; j <= n; j++)
    //     {
    //         printf("%2d ", cha[i][j]);
    //     }
    //     printf("\n");
    // }
    // printf("\n");
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            printf("%d ", cha[i][j] += cha[i][j - 1]);
        }
        printf("\n");
    }
}