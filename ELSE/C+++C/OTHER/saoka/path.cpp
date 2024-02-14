// #include "stdafx.h"
#include "malloc.h"
#include <stdio.h>
#include <iostream>
#include <iomanip>
using namespace std;
#define MVNum 100
#define Maxint 32767
enum boolean
{
    FALSE,
    TRUE
};
typedef int VertexType;
typedef int Adjmatrix;
typedef struct
{
    VertexType vexs[MVNum];
    Adjmatrix arcs[MVNum][MVNum];
} MGraph;
int D1[MVNum], P1[MVNum];
int D[MVNum][MVNum], P[MVNum][MVNum];

void CreateMGraph(MGraph *G, int n, int e)
{ // 采用邻接矩阵表示法构造有向图G，n，e表示图的当前顶点数和边数
    int i, j, k, w;
    for (i = 1; i <= n; i++)
        G->vexs[i] = i;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            G->arcs[i][j] = Maxint; // 初始化邻接矩阵
    cout << "输入" << e << "条边的i、j及w" << endl;
    for (k = 1; k <= e; k++)
    {
        cin >> i >> j >> w;
        G->arcs[i][j] = w;
    }
    cout << "有向图的存储结构建立完毕" << endl;
}

void Dijkstra(MGraph *G, int v1, int n)
{
    int D2[MVNum], P2[MVNum];
    int v, i, w, min;
    enum boolean S[MVNum];
    for (v = 1; v <= n; v++)
    {
        S[v] = FALSE;
        D2[v] = G->arcs[v1][v];
        if (D2[v] < Maxint)
            P2[v] = v1;
        else
            P2[v] = 0;
    }
    D2[v1] = 0;
    S[v1] = TRUE; // 初始化
    for (i = 2; i < n; i++)
    {
        min = Maxint;
        for (w = 1; w <= n; w++)
            if (!S[w] && D2[w] < min) // 找a点到零界点最小的路径
            {
                v = w;
                min = D2[w];
            }
        S[v] = TRUE;
        for (w = 1; w <= n; w++)
            if (!S[w] && D2[v] + G->arcs[v][w] < D2[w])
            {
                D2[w] = D2[v] + G->arcs[v][w];
                P2[w] = v;
            }
    }
    cout << "路径长度路径" << endl;
    for (i = 1; i <= n; i++)
    {
        cout << setw(5) << D2[i];
        cout << setw(5) << i;
        v = P2[i];
        while (v != 0)
        {
            cout << v;
            v = P2[v];
        }
        cout << endl;
    }
}

void Floyd(MGraph *G, int n)
{
    int i, j, k, w;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
        {
            if (G->arcs[i][j] != Maxint)
                P[i][j] = j;
            else
                P[i][j] = 0;
            D[i][j] = G->arcs[i][j];
        }
    for (k = 1; k <= n; k++)
    {
        for (i = 1; i <= n; i++)
            for (j = 1; j <= n; j++)
            {
                if (D[i][k] + D[k][j] < D[i][j])
                {
                    D[i][j] = D[i][k] + D[k][j];
                    P[i][j] = P[i][k];
                }
            }
    }
}

int main()
{
    MGraph *G;
    int m, n, e, v, w, k;
    int xz = 1;
    G = (MGraph *)malloc(sizeof(MGraph));
    cout << "输入图中顶点个数和边数n,e:" << endl;
    cin >> n >> e;
    CreateMGraph(G, n, e);
    while (xz != 0)
    {
        cout << "********求城市之间的最短路径********" << endl;
        cout << "====================================" << endl;
        cout << "1.求一个城市到所有城市的最短路径\n"
             << endl;
        cout << "2.求任意的两个城市之间的最短路径\n"
             << endl;
        cout << "====================================" << endl;
        cout << "请选择： 1、或 2、选择 0、退出：" << endl;
        cin >> xz;
        if (xz == 2)
        {
            Floyd(G, n);
            cout << "输入源点(或称起点)和终点:v,w:" << endl;
            cin >> v >> w;
            k = P[v][w];
            if (k == 0)
                cout << "顶点" << v << "到" << w << "无路径!" << endl;
            else
            {

                cout << "从顶点" << v << "到" << w << "的最短路径是：" << v << endl;
                while (k != w)
                {
                    cout << "->" << k;
                    k = P[k][w];
                }
                cout << "->" << w;
                cout << "路径长度:" << D[v][w] << endl;
            }
        }
        else if (xz == 1)
        {
            cout << "求单源路径，输入源点v:";
            cin >> v;
            Dijkstra(G, v, n);
        }
    }
    cout << "结束求最短路径,再见!" << endl;
}
