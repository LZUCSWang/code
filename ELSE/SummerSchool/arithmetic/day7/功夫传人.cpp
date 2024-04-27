#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#define MAX 100005
// 10 18.0 1.00
// 3 2 3 5
// 1 9
// 1 4
// 1 7
// 0 7
// 2 6 1
// 1 8
// 0 9
// 0 4
// 0 3
int n;
double z, r;
vector<int> datas[MAX];
int times[MAX];
void input()
{
    cin >> n >> z >> r;
    r = (100 - r) / 100.0;
    for (int i = 0; i < n; i++)
    {
        int k;
        cin >> k;
        switch (k)
        {
        case 0:
            cin >> times[i];
            break;

        default:
            for (int j = 1; j <= k; j++)
            {
                int x;
                cin >> x;
                datas[i].push_back(x);
            }
            break;
        }
    }
}
double sums;
void dfs(int now, double this_power)
{
    switch (times[now])
    {
    case 0:
        for (int i = 0; i < datas[now].size(); i++)
        {
            int nexts = datas[now][i];
            dfs(nexts, this_power * r);
        }
        break;
    default:
        sums += this_power * times[now];
        break;
    }
}
int main()
{
    input();
    dfs(0, z);
    printf("%d\n", int(sums));
}