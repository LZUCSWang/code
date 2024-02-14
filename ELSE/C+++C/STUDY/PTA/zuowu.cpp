#include <bits/stdc++.h>
using namespace std;
#define MAXN 100000
int N, M, K, T;
int t[MAXN];
bool have[MAXN];
// map<int, pair<int, int>> mp;
vector<pair<int, int>> mp[MAXN];
int ans[MAXN];
int time_cost(int target)
{
    // if (have[target])
    //     return t[target];
    // int time = max(time_cost(mp[target].first), time_cost(mp[target].second));
    // // return max(time_cost(mp[target].first), time_cost(mp[target].second));
    // return time + t[target];
    for (int i = 0; i < mp[target].size(); i++)
    {
        int a = mp[target][i].first, b = mp[target][i].second;
        if (!have[a])
            time_cost(a);
        if (!have[b])
            time_cost(b);
        if (have[a] && have[b])
        {
            have[target] = true;
            ans[target] = min(ans[target], max(ans[a], ans[b]) + max(t[a], t[b]));
        }
    }
    return ans[target];
}
int main()
{
    scanf("%d%d%d%d", &N, &M, &K, &T);
    memset(ans, 0x3f, sizeof(ans));
    for (int i = 1; i <= N; i++)
    {
        scanf("%d", t + i);
    }
    for (int i = 1; i <= M; i++)
    {
        int temp;
        scanf("%d", &temp);
        have[temp] = true;
        ans[temp] = 0;
    }
    int a, b, c;
    for (int i = 0; i < K; i++)
    {
        scanf("%d%d%d", &a, &b, &c);
        mp[c].push_back({a, b});
    }
    printf("%d", time_cost(T));
    return 0;
}