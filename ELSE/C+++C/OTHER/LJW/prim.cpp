#include <iostream>
using namespace std;

typedef char VerTexType;
typedef int ArcType;
#define MVNum 100
#define MaxInt 32767 //表示极大值，即∞
ArcType closedge[MVNum];

//- - - - -图的邻接表存储表示- - - - -
typedef char VerTexType; //假设顶点的数据类型为字符型
typedef int ArcType;     //假设边的权值类型为整型
typedef struct
{
    // VerTexType vexs[MVNum];     //顶点表
    ArcType arcs[MVNum][MVNum]; //邻接矩阵
    int vexnum;       //图的当前点数和边数
} AMGraph;

void CreateUDN(AMGraph &G)
{
    int i, j, k;
    cin >> G.vexnum;
    for (i = 1; i < G.vexnum; ++i)
        for (j = 1; j < G.vexnum; ++j)
        {
            cin >> k;
                G.arcs[i][j] = k;
        }
}

int Min(AMGraph G)
{
    //返回边权值最小的点。该点将是Prim算法，即"加点法"要新加的点
    int i;
    int index = -1;
    int min = MaxInt;
    for (i = 0; i < G.vexnum; ++i)
    {
        if (min > closedge[i] && closedge[i] != 0)
        {
            min = closedge[i];
            index = i;
        }
    }
    return index;
} // Min

int MiniSpanTree_Prim(AMGraph G, int u)
{
    //无向网G以邻接矩阵形式存储，从顶点u出发构造G的最小生成树T，输出T的各条边
    int k, j, i, cnt = 0, sum = 0;
    for (i = 1; i < G.vexnum; i++)
    {
        k = Min(G);
        cnt += closedge[k];
        closedge[k] = 0;
        for (j = 1; j <= G.vexnum; j++)
        {
            if (G.arcs[k][j] < closedge[j])
                closedge[j] = G.arcs[k][j];
        }
    }
    return cnt;

} // MiniSpanTree_Prim

int main()
{
    //	cout << "************算法6.8　普里姆算法**************" << endl << endl;
    AMGraph G;
    CreateUDN(G);
    cout << MiniSpanTree_Prim(G, 1);
    cout << endl;
    return 0;
} // main
