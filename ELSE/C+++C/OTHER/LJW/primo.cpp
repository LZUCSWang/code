#include <iostream>
using namespace std;

// typedef int VerTexType;
#define MVNum 100
#define MaxInt 32767 //表示极大值，即∞
//辅助数组的定义，用来记录从顶点集U到V-U的权值最小的边
struct
{
    int adjvex;      //最小边在U中的那个顶点
    ArcType lowcost; //最小边上的权值
} closedge[MVNum];
//- - - - -图的邻接表存储表示- - - - -
typedef int ArcType; //假设边的权值类型为整型
typedef struct
{
    int vexs[MVNum];            //顶点表
    ArcType arcs[MVNum][MVNum]; //邻接矩阵
    int vexnum, arcnum;         //图的当前点数和边数
} AMGraph;

int LocateVex(AMGraph G, int v)
{
    //确定点v在G中的位置
    for (int i = 0; i < G.vexnum; ++i)
        if (G.vexs[i] == v)
            return i;
    return -1;
} // LocateVex
void CreateUDN(AMGraph &G)
{
    //采用邻接矩阵表示法，创建无向网G
    int i, j, k;
    //	cout <<"请输入总顶点数，总边数，以空格隔开:";
    cin >> G.vexnum; //输入总顶点数，总边数
    G.arcnum = 0;
    //	cout << "输入点的名称，如a" << endl;
    for (i = 0; i < G.vexnum; i++)
    {
        G.vexs[i] = i + 1;
    }
    for (i = 0; i < G.vexnum; ++i) //初始化邻接矩阵，边的权值均置为极大值MaxInt
        for (j = 0; j < G.vexnum; ++j)
            G.arcs[i][j] = MaxInt;
    //	cout << "输入边依附的顶点及权值，如a b 5" << endl;
    for (i = 0; i < G.vexnum; ++i)
        for (j = 0; j < G.vexnum; ++j)
        { //构造邻接矩阵
            // VerTexType v1, v2;
            ArcType w;
            //		cout << "请输入第" << (k + 1) << "条边依附的顶点及权值:";
            cin >> w; //输入一条边依附的顶点及权值
            if (w != 0)
                G.arcnum++;
            // i = LocateVex(G, v1);
            // j = LocateVex(G, v2);
            if (w != 0)           //确定v1和v2在G中的位置，即顶点数组的下标
                G.arcs[i][j] = w; //边<v1, v2>的权值置为w
            // /G.arcs[j][i] = G.arcs[i][j]; //置<v1, v2>的对称边<v2, v1>的权值为w
        }
} // CreateUDN

int Min(AMGraph G)
{
    //返回边权值最小的点。该点将是Prim算法，即"加点法"要新加的点
    int i;
    int index = -1;
    int min = MaxInt;
    for (i = 0; i < G.vexnum; ++i)
    {
        if (min > closedge[i].lowcost && closedge[i].lowcost != 0)
        {
            min = closedge[i].lowcost;
            index = i;
        }
    } // for
    return index;
} // Min

int MiniSpanTree_Prim(AMGraph G, int u)
{
    //无向网G以邻接矩阵形式存储，从顶点u出发构造G的最小生成树T，输出T的各条边
    int k, j, i, cnt = 0, sum = 0;
    int u0, v0;
    //将本函数实现完整 begin
    k = LocateVex(G, u);
    for (j = 0; j < G.vexnum; j++)
        if (j != k)
            closedge[j] = {u, G.arcs[k][j]};
    closedge[k].lowcost = 0;
    for (i = 1; i < G.vexnum; i++)
    {
        k = Min(G);
        u0 = closedge[k].adjvex;
        v0 = G.vexs[k];
        cnt = cnt + closedge[k].lowcost;
        // cout << '(' << u0 << ',' << v0 << ')' << ':' << sum << endl;
        closedge[k].lowcost = 0;
        for (j = 0; j < G.vexnum; j++)
        {
            if (G.arcs[k][j] < closedge[j].lowcost)
                closedge[j] = {G.vexs[k], G.arcs[k][j]};
        }
    }
    //将本函数实现完整 end
    // cout << "minCost=";
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
