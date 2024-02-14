#include <bits/stdc++.h>
using namespace std;

int num[4];
int ans, tot;
void dfs(int res, int lastNums, int nowColor)
{
    if (res == 0)
    {
        ans++;
        return;
    }
    for (int i = 1; i <= 3; i++)
    {
        if (i == nowColor)
            continue;
        for (int j = lastNums + 1; j <= num[i]; j++)
        {
            num[i] -= j;
            if (res >= j)
            {
                dfs(res - j, j, i);
            }
            num[i] += j;
        }
    }
}
int main()
{
    for (int i = 1; i <= 3; i++)
    {
        cin >> num[i];
        tot += num[i];
    }
    dfs(tot, 0, 0);
    cout<<ans<<endl;
}