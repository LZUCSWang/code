#include <bits/stdc++.h>
using namespace std;
#define MAXN 10005
typedef long long ll;
// ll a[MAXN];
ll n, m;
int ans = 0x3f3f3f3f;
vector<int> pos[MAXN];
bool know[MAXN][MAXN]; // 第i个学生知道第j个学生的情况
bool check(int kao, int peo)
{
    for (int i = 0; i < pos[kao].size(); i++)
    {
        if (know[peo][pos[kao][i]])
            return false;
    }
    return true;
}
void dfs(int now, int has) // now:当前学生，has:已经安排的考场数量
{
    if (has >= ans)
    {
        return;
    }
    if (now == n + 1) // 已经安排完所有学生
    {
        ans = min(ans, has);
        return;
    }
    for (int i = 1; i <= has; i++)
    {
        if (check(i, now))
        {
            pos[i].push_back(now);
            dfs(now + 1, has);
            pos[i].pop_back();
        }
    }
    if (has + 1 <= n)
    {
        pos[has + 1].push_back(now);
        dfs(now + 1, has + 1);
        pos[has + 1].pop_back();
    }
}
int main()
{
    cin >> n >> m;
    while (m--)
    {
        int x, y;
        cin >> x >> y;
        know[x][y] = know[y][x] = true;
    }
    dfs(1, 0);
    cout << ans << endl;
}