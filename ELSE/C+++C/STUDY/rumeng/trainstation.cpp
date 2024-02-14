// https://www.luogu.com.cn/problem/P1983
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 1005
// 9 2
// 4 1 3 5 6
// 3 3 5 6
int n, m, nums, station[MAX], tupo[MAX][MAX], dutt[MAX];
bool is[MAX];
void build()
{
    cin >> n >> m;
    while (m--)
    {
        memset(is, 0, sizeof(is));
        scanf("%d", &nums);
        for (int i = 1; i <= nums; i++)
        {
            scanf("%d", station + i);
            is[station[i]] = true;
        }
        for (int i = station[1]; i <= station[nums]; i++)
        {
            if (!is[i])
                for (int j = 1; j <= nums; j++)
                {
                    if (!tupo[i][station[j]])
                    {
                        tupo[i][station[j]] = 1;
                        dutt[station[j]]++;
                    }
                }
        }
    }
}
stack<int> S;
int ans;
bool flag[MAX];
void tu()
{
    while (true)
    {
        for (int i = 1; i <= n; i++)
        {
            if (!dutt[i] && !flag[i])
            {
                S.push(i);
                flag[i] = true;
            }
        }
        if (S.empty())
            break;
        while (!S.empty())
        {
            int t = S.top();
            S.pop();
            for (int i = 1; i <= n; i++)
            {
                if (tupo[t][i])
                {
                    tupo[t][i] = 0;
                    dutt[i]--;
                }
            }
        }
        ans++;
    }
    printf("%d", ans);
}
int main()
{
    build();
    tu();
}