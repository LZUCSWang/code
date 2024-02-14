#include <iostream>
#include <cstring>
using namespace std;
typedef struct
{
    int weight;
    int parent, lchild, rchild;
} HTNode, *HuffmanTree;
typedef char **HuffmanCode;

void Select(HuffmanTree HT, int len, int &s1, int &s2)
{
    /****在此下面完成代码***************/
    int i, k, t;
    int min1 = 99999, min2 = 99999;
    for (i = 1; i <= len; i++)
    {
        if (HT[i].parent == 0 && HT[i].weight < min1)
        {
            min1 = HT[i].weight;
            k = i;
        }
    }
    s1 = k;
    for (i = 1; i <= len; i++)
    {
        if (HT[i].parent == 0 && HT[i].weight < min2 && i != k)
        {
            min2 = HT[i].weight;
            t = i;
        }
    }
    s2 = t;

    /***********************************/
}

//用算法5.10构造赫夫曼树
void CreatHuffmanTree(HuffmanTree &HT, int n)
{
    //构造赫夫曼树HT
    int m, s1, s2, i;
    if (n <= 1)
        return;
    m = 2 * n - 1;
    HT = new HTNode[m + 1]; // 0号单元未用，所以需要动态分配m+1个单元，HT[m]表示根结点
    int flag[m + 1];
    for (i = 1; i <= m; ++i)
    { //将1~m号单元中的双亲、左孩子，右孩子的下标都初始化为0
        HT[i].parent = 0;
        HT[i].lchild = 0;
        HT[i].rchild = 0;
    }
    // cout<<"请输入叶子结点的权值：\n";
    for (i = 1; i <= n; ++i) //输入前n个单元中叶子结点的权值
        cin >> HT[i].weight;
    flag[i] = HT[i].weight;
    /*――――――――――初始化工作结束，下面开始创建赫夫曼树――――――――――*/
    for (i = n + 1; i <= m; ++i)
    {
        //通过n-1次的选择、删除、合并来创建赫夫曼树
        Select(HT, i - 1, s1, s2);
        //在HT[k](1≤k≤i-1)中选择两个其双亲域为0且权值最小的结点,
        // 并返回它们在HT中的序号s1和s2
        HT[s1].parent = i;
        HT[s2].parent = i;
        //得到新结点i，从森林中删除s1，s2，将s1和s2的双亲域由0改为i
        int sj1 = 0, sj2 = 0;
        for (int j = 1; j <= n and (sj1 == 0 or sj2 == 0); ++j)
        {
            if (flag[j] == s1 and sj1 == 0)
            {
                sj1 = j;
                flag[j] = 0;
            }
            if (flag[j] == s2 and sj2 == 0)
            {
                sj2 = j;
                flag[j] = 0;
            }
        }
        if (sj1 > sj2)
        {
            int t = s1;
            s1 = s2;
            s2 = t;
        }
        HT[i].lchild = s1;
        HT[i].rchild = s2;                            // s1,s2分别作为i的左右孩子
        HT[i].weight = HT[s1].weight + HT[s2].weight; // i 的权值为左右孩子权值之和
    }                                                 // for
} // CreatHuffmanTree
void creathuffmancode(HuffmanTree HT, HuffmanCode &HC, int n)
{
    HC = new char *[n + 1];
    char *cd = new char[n];
    cd[n - 1] = '\0';
    int i, c, f, start;
    for (i = 1; i <= n; i++)
    {
        start = n - 1;
        c = i;
        f = HT[i].parent;
        while (f != 0)
        {
            --start;
            if (HT[f].lchild == c)
                cd[start] = '0';
            else
                cd[start] = '1';
            c = f;
            f = HT[f].parent;
        }
        HC[i] = new char[n - start];
        strcpy(HC[i], &cd[start]);
    }

    delete cd;
    for (i = 1; i <= n; i++)
    {
        cout << HC[i] << endl;
    }
}
int main()
{
    HuffmanTree HT;
    HuffmanCode HC;
    int n;
    cin >> n; //输入赫夫曼树的叶子结点个数
    CreatHuffmanTree(HT, n);
    creathuffmancode(HT, HC, n);
    return 0;
}
