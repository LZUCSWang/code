// bellman-ford algorithm
// Bellman-Ford algorithm is a shortest path algorithm for a graph with negative edge weights.
// Bellman-Ford algorithm is used to find the shortest path from a source vertex to all other vertices in a graph.
// Bellman-Ford algorithm is also used to find the shortest path from a source vertex to all other vertices in a graph.
//最短路径 - Bellman_Ford算法  参数：图G、源点v 作用：计算不含负圈图的最短路径 返回是否有圈
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX_INT 0x3f3f3f3f
#define MAX_N 101
typedef struct Graph
{
    int vexnum, arcnum;
    int Edge[MAX_N][MAX_N];
} Graph;
int n, e, m;
Graph G;
int D[MAX_N];
bool Bellman_Ford(Graph G, int v)
{
    //初始化
    memset(D, MAX_INT, sizeof(D));
    for (int i = 0; i < n; i++)
    {
        D[i] = G.Edge[v][i];
    }
    D[v] = 0;
    //初始化结束，开始双重循环
    for (int i = 2; i < G.vexnum - 1; i++)
        for (int j = 0; j < G.vexnum; j++)     // j为源点
            for (int k = 0; k < G.vexnum; k++) // k为终点
                if (D[k] > D[j] + G.Edge[j][k])
                {
                    D[k] = D[j] + G.Edge[j][k];
                }
    //判断是否含有负圈
    bool flag = true;
    for (int j = 0; j < G.vexnum; j++)     // j为源点
        for (int k = 0; k < G.vexnum; k++) // k为终点
            if (D[k] > D[j] + G.Edge[j][k])
            {
                flag = false;
                break;
            }
    return flag;
}
void input()
{
    if (scanf("%d%d%d", &n, &e, &m) == EOF)
        exit(0);
    G.vexnum = n;
    G.arcnum = e;
    memset(G.Edge, MAX_INT, sizeof(G.Edge));
    for (int i = 0; i < e; i++)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        G.Edge[a][b] = c;
    }
}

int main()
{
    while (1)
    {
        bool flag = true;
        input();
        for (int i = 1; i <= m; i++)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            if (Bellman_Ford(G, x) && flag)
            {
                if (D[y] == MAX_INT)
                    printf("none\n");
                else
                    printf("%d\n", D[y]);
            }
            else if (flag)
            {
                printf("negative circle\n");
                // break;
                flag = false;
            }
        }
    }
}