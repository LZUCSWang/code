#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 10001
const ll INF = 10e9;
ll n, m, tim[MAX], graph[MAX][MAX], q;

void init()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            graph[i][j] = graph[j][i] = INF;
        }
    }
}
void input()
{
    cin >> n >> m;
    init();
    for (int i = 0; i < n; i++)
    {
        scanf("%d", tim + i);
    }
    while (m--)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        graph[a][b] = c;
        graph[b][a] = c;
    }
}

void work()
{
    cin >> q;
    int now_cun = 0;
    while (q--)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        while (tim[now_cun] <= c && now_cun < n)
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (graph[i][j] > graph[i][now_cun] + graph[now_cun][j])
                    {
                        graph[i][j] = graph[j][i] = graph[i][now_cun] + graph[now_cun][j];
                    }
                }
            }
            now_cun++;
        }
        if (tim[a] > c || tim[b] > c || graph[a][b] == INF)
            printf("-1\n");
        else
            printf("%d\n", graph[a][b]);
    }
}
int main()
{
    input();
    work();
}