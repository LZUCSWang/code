#include <iostream>
#include <iomanip>
#include <cstdio>
using namespace std;

#define MVNum 100
#define ERROR -1
#define OK 1
typedef int ArcType;
typedef int Status;
typedef struct
{                            //顶点表
    ArcType datas[MVNum][MVNum]; //邻接矩阵
    int vexnum, arcnum;      //图的当前点数和边数
} Graph;
void CreateUDG(Graph &g)
{
    int i, j;
    for (i = 0; i < g.vexnum; i++)
        for (j = 0; j < g.vexnum; j++)
            cin >> g.datas[i][j];
}
Status topo(Graph g, int n)
{
    int indegree[100] = {0};
    int stack[100];
    int front = 0;
    int real = 0;
    int i, j, count = 0, v;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (g.datas[i][j] != 0)
                indegree[j]++;
    for (i = 0; i < n; i++)
        if (!indegree[i])
            stack[real++] = i;
    while (front != real)
    {
        v = stack[--real];
        cout << v << " ";
        count++;
        for (i = 0; i < n; i++)
        {
            if (g.datas[v][i] != 0)
            {
                indegree[i] = indegree[i] - 1;
                if (!indegree[i])
                    stack[real++] = i;
            }
        }
    }
    if (count < n)
        return ERROR;
    return OK;
}
int main()
{
    Graph g;
    int n;
    cin >> n;
    g.vexnum = n;
    CreateUDG(g);
    topo(g, n);
    return 0;
}
