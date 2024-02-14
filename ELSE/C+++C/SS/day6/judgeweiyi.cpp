#include <bits/stdc++.h>
#define maxn 505
#define INF 0x3f3f3f3f
using namespace std;
struct Line
{
    int l, r, w;
    Line(int l, int r, int w) : l(l), r(r), w(w) {}
    bool operator<(const Line &a) const
    {
        return w < a.w;
    }
};
vector<Line> line;
int par[maxn];
int f(int p)
{
    return p == par[p] ? p : par[p] = f(par[p]);
}
int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int l, r, w;
        cin >> l >> r >> w;
        line.push_back(Line(l, r, w));
    }
    sort(line.begin(), line.end());
    int sum = 0;                 //最小生成树的值
    int maxd[maxn][maxn] = {0};  //最小生成树中从i到j的边里最大的
    int cnt = 0;                 //添加的边数
    bool vis[maxn * maxn] = {0}; //边i是否在最小生成树里
    for (int i = 1; i <= n; i++)
        par[i] = i;
    for (int i = 0; i < m; i++)
    {
        int l = f(line[i].l);
        int r = f(line[i].r);
        if (l != r)
        {
            cnt++;
            vis[i] = true;
            for (int k = 1; k <= n; k++)
            { //枚举所有属于集合l的边
                if (f(k) != l)
                    continue;
                for (int j = 1; j <= n; j++)
                { //枚举所有属于集合r的边
                    if (f(j) == r)
                    {                                        //两个集合的点，到另一个集合的所有点都会经边i
                        maxd[k][j] = maxd[j][k] = line[i].w; //且边是递增的，所以两点间的当前最长边就是i
                    }
                }
            }
            sum += line[i].w;
            par[l] = r;
        }
        if (cnt == n - 1)
            break;
    }
    if (cnt != n - 1)
    {
        cout << "No MST" << endl;
        set<int> s;
        for (int i = 1; i <= n; i++) // set记录集合数
            s.insert(f(i));
        cout << s.size() << endl;
    }
    else
    {
        cout << sum << endl;
        int dis = INF;
        for (int i = 0; i < m; i++)
        { //求次小生成树
            if (!vis[i])
                if (line[i].w == maxd[line[i].l][line[i].r])
                {
                    cout << "No" << endl;
                    return 0; //最小生成树+此边-环中最长边
                }
        }
        cout << "Yes" << endl;
    }
    return 0;
}