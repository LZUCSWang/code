#include <bits/stdc++.h>
using namespace std;
int n, e, m;
#define MAX 1005
int G[MAX][MAX];
const int INF = 0x3f3f3f3f;
int main()
{
    cin >> n >> e >> m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i != j)
            {
                G[i][j] = INF;
            }
        }
    }
    for (int i = 1; i <= e; i++)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        G[a][b] = 1;
        G[b][a] = 1;
    }
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (G[i][k] + G[k][j] < G[i][j])
                {
                    G[i][j] = G[i][k] + G[k][j];
                }
            }
        }
    }
    for (int i = 1; i <= m; i++)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        printf("%d\n", G[a][b]);
    }
}